#include "stdafx.h"

#include "resources.h"

#include "core/sync.h"
#include "engine.h"

using namespace engine;

Resource Resource::Null;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Resources::Resources() : items_(Resource::Null), events_(handles_, sizeof(handles_) / sizeof(HANDLE), 2) {
	for (uint i = 0; i < SLOT_COUNT; ++i)
		slots_[i].status = Slot::Vacant;

	handles_[0] = Sync::inst().exit.handle();
	handles_[1] = newResource_.handle();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::update() {
	kaynine::AutoLock<> lock(guard_);

	for (unsigned check = events_.checkAny(); check != WAIT_OBJECT_0 && check != WAIT_TIMEOUT && check != WAIT_FAILED && check != WAIT_ABANDONED; check = events_.checkAny())
		if (check == WAIT_OBJECT_0 + 1) {	// new resource
			schedule();
			newResource_.reset();
		} else if (WAIT_OBJECT_0 + 2 <= check && check < WAIT_OBJECT_0 + SLOT_COUNT + 2) {	// asio complete
			complete(check - WAIT_OBJECT_0 - 2);
			schedule(check - WAIT_OBJECT_0 - 2);
		}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const uint Resources::add(const TCHAR* const path, kaynine::MemoryPool& pool) {
	assert(path);

	kaynine::AutoLock<> lock(guard_);

	// look through already added resources
	Items::Range range(items_);
	for (; !range.finished(); range.next())
		if (!_tcscmp(path, range.get().path)) {
			assert(range.get().pool == &pool);

			return range.index();
		}

	const uint added = items_.add(Resource(path, &pool, NULL, 0, Resource::Pending));
	newResource_.set();

	return added;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Resources::remove(const uint resource) {
	kaynine::AutoLock<> lock(guard_);

	items_.remove(resource);
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::schedule(const unsigned first /*= 0*/) {
	assert(first < SLOT_COUNT);

	TRACE_NOTICE(_T("checking for the new resources to load at the slot #%d"), first);

	Items::Range range(items_);
	for (uint slot = first; slot < SLOT_COUNT && !range.finished(); ++slot) {
		if (slots_[slot].status == Slot::Vacant) {
			while (!range.finished() && range.get().status != Resource::Pending)
				range.next();

			if (!range.finished()) {
				load(range.index(), slot);
				range.next();
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::load(const uint item, const uint slot) {
	assert(item < MAX_RESOURCES && slot < SLOT_COUNT);

	TRACE_NOTICE(_T("loading '%s' in slot #%d"), items_[item].path, slot);

	// open the file
	const HANDLE file = ::CreateFile(items_[item].path, 
									 GENERIC_READ, 
									 FILE_SHARE_READ, 
									 NULL, 
									 OPEN_EXISTING, 
									 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN,
									 NULL);
	if (file == INVALID_HANDLE_VALUE) {
		items_[item].status = Resource::Error;
		TRACE_WARNING(_T("couldn't open file '%s'"), items_[item].path);
		return;
	}
	
	// file size
	const DWORD size = ::GetFileSize(file, NULL);
	if (!size) {
		::CloseHandle(file);

		items_[item].status = Resource::Error;
		TRACE_WARNING(_T("couldn't load empty file '%s'"), items_[item].path);
		return;
	}

	// allocate memory for file's contents
	void* const buffer = items_[item].pool->allocate(size + sizeof(TCHAR));
	assert(buffer);
	*reinterpret_cast<TCHAR*>((unsigned)buffer + size) = _T('\0');

	// prepare asio struct
	memset(&slots_[slot].overlapped, 0, sizeof(slots_[slot].overlapped));

	assert(!events_.check(slot + 2));
	slots_[slot].overlapped.hEvent = events_.handle(slot + 2);
	
	// initiate asio read
	DWORD read = 0;
	if (!::ReadFile(file, buffer, size, &read, &slots_[slot].overlapped) && ::GetLastError() != ERROR_IO_PENDING) {
		::CloseHandle(file);
		TRACE_WARNING(_T("couldn't read file '%s'"), items_[item].path);

		items_[item].status = Resource::Error;
	} else {
		items_[item].buffer = buffer;
		items_[item].size = size;
		items_[item].status = Resource::Processing;
		
		slots_[slot].resource = item;
		slots_[slot].file = file;
		slots_[slot].status = Slot::Processing;
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::complete(const unsigned slot) {
	assert(slots_[slot].status == Slot::Processing);

	Resource& resource = items_[slots_[slot].resource];

	if (!items_.valid(slots_[slot].resource)) {
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

	CHECKED_CALL_A(::CloseHandle(slots_[slot].file));
	events_.reset(slot + 2, 1);

	slots_[slot].status = Slot::Vacant;
}

//---------------------------------------------------------------------------------------------------------------------
