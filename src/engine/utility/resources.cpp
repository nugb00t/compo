#include "stdafx.h"

#include "resources.h"

#include "core/sync.h"
#include "engine.h"

using namespace engine;

Resource Resource::Null;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Resources::Resources() : resources_(Resource::Null), vacant_(0), events_(handles_, sizeof(handles_) / sizeof(HANDLE), 0, SLOT_COUNT) {
	for (uint i = 0; i < SLOT_COUNT; ++i)
		slots_[i].status = Slot::Vacant;

	handles_[SLOT_COUNT + 0] = newResource_.handle();
	handles_[SLOT_COUNT + 1] = Sync::inst().exit.handle();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::update() {
	assert(vacant_ < MAX_RESOURCES - 1);

	for (unsigned wait = events_.waitAny(); wait != WAIT_OBJECT_0 + SLOT_COUNT + 1 && wait != WAIT_FAILED && wait != WAIT_ABANDONED; wait = events_.waitAny())
		if (wait == WAIT_OBJECT_0 + SLOT_COUNT) {	// new resource
			kaynine::AutoLock<> lock(guard_);

			schedule();
			newResource_.reset();
		} else if (WAIT_OBJECT_0 <= wait && wait < WAIT_OBJECT_0 + SLOT_COUNT) {
			kaynine::AutoLock<> lock(guard_);

			complete(wait - WAIT_OBJECT_0);
			schedule(wait - WAIT_OBJECT_0);
		}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Resources::reset() {
	kaynine::AutoLock<> lock(guard_);

	vacant_ = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const uint Resources::add(const TCHAR* const path, kaynine::MemoryPool& pool) {
	kaynine::AutoLock<> lock(guard_);

	assert(vacant_ < MAX_RESOURCES - 1 && path);

	resources_[vacant_] = Resource(path, &pool, NULL, 0, Resource::Pending);

	newResource_.set();

	return vacant_++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Resources::remove(const uint resource) {
	resources_.remove(resource);
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::load(const uint item, const uint slot) {
	assert(item < MAX_RESOURCES && slot < SLOT_COUNT);

	TRACE_NOTICE(_T("loading '%s' in slot #%d"), resources_[item].path, slot);

	// open the file
	const HANDLE file = ::CreateFile(resources_[item].path, 
									 GENERIC_READ, 
									 FILE_SHARE_READ, 
									 NULL, 
									 OPEN_EXISTING, 
									 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN,
									 NULL);
	if (file == INVALID_HANDLE_VALUE) {
		resources_[item].status = Resource::Error;
		TRACE_WARNING(_T("couldn't open file '%s'"), resources_[item].path);
		return;
	}
	
	// file size
	const DWORD size = ::GetFileSize(file, NULL);
	if (!size) {
		::CloseHandle(file);

		resources_[item].status = Resource::Error;
		TRACE_WARNING(_T("couldn't load empty file '%s'"), resources_[item].path);
		return;
	}

	// allocate memory for file's contents
	void* const buffer = resources_[item].pool->allocate(size + sizeof(TCHAR));
	assert(buffer);
	*reinterpret_cast<TCHAR*>((unsigned)buffer + size) = _T('\0');

	// prepare asio struct
	memset(&slots_[slot].overlapped, 0, sizeof(slots_[slot].overlapped));

	assert(!events_.isSet(slot));
	slots_[slot].overlapped.hEvent = events_.handle(slot);
	
	// initiate asio read
	DWORD read = 0;
	if (!::ReadFile(file, buffer, size, &read, &slots_[slot].overlapped) && ::GetLastError() != ERROR_IO_PENDING) {
		::CloseHandle(file);
		TRACE_WARNING(_T("couldn't read file '%s'"), resources_[item].path);

		resources_[item].status = Resource::Error;
	} else {
		resources_[item].buffer = buffer;
		resources_[item].size = size;
		resources_[item].status = Resource::Processing;
		
		slots_[slot].resource = item;
		slots_[slot].file = file;
		slots_[slot].status = Slot::Processing;
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::schedule(const unsigned first /*= 0*/) {
	assert(first < SLOT_COUNT);

	if (!first)
		TRACE_NOTICE(_T("checking for the new resources to load.."));
	else
		TRACE_NOTICE(_T("checking for the new resources to load at the slot #%d"), first);

	for (uint slot = first, item = 0; slot < SLOT_COUNT && item < vacant_; ++slot) {
		if (slots_[slot].status == Slot::Vacant) {
			while (resources_[item].status != Resource::Pending && item < vacant_)
				++item;

			if (item < vacant_)
				load(item++, slot);
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::complete(const unsigned slot) {
	assert(slots_[slot].status == Slot::Processing);

	Resource& resource = resources_[slots_[slot].resource];

	if (slots_[slot].resource >= vacant_) {
		TRACE_WARNING(_T("resource #%3d '%s' was discarded at the slot #%d"), slots_[slot].resource, resource.path, slot);
		return;
	}

	if (slots_[slot].overlapped.InternalHigh == resource.size) {
		TRACE_GOOD(_T("resource #%d '%s' was successfully loaded at the slot #%d"), slots_[slot].resource, resource.path, slot);
		resource.status = Resource::Done;
	} else {
		TRACE_WARNING(_T("resource #%d '%s' failed to load at the slot #%d"), slots_[slot].resource, resource.path, slot);
		resource.status = Resource::Error;
	}

	CHECKED_WINAPI_CALL_A(::CloseHandle(slots_[slot].file));
	events_.reset(slot, 1);

	slots_[slot].status = Slot::Vacant;
}

//---------------------------------------------------------------------------------------------------------------------
