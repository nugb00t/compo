#include "stdafx.h"

#include "resources.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Resources::Resources() : vacant_(0), events_(handles_, sizeof(handles_) / sizeof(HANDLE), 0, SLOT_COUNT) {
	for (uint i = 0; i < SLOT_COUNT; ++i)
		slots_[i].status = Slot::Vacant;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::initialize() {
	handles_[SLOT_COUNT + 0] = newResource_.handle();
	handles_[SLOT_COUNT + 1] = g_engine.sync->exit.handle();

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::update() {
	assert(vacant_ < MAX_RESOURCES - 1);

	for (unsigned wait = events_.waitAny(); wait != WAIT_OBJECT_0 + SLOT_COUNT + 1 && wait != WAIT_FAILED && wait != WAIT_ABANDONED; wait = events_.waitAny())
		if (wait == WAIT_OBJECT_0 + SLOT_COUNT) {	// new resource
			schedule();
			newResource_.reset();
		} else if (WAIT_OBJECT_0 <= wait && wait < WAIT_OBJECT_0 + SLOT_COUNT) {
			complete(wait - WAIT_OBJECT_0);
			schedule(wait - WAIT_OBJECT_0);
		}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Resources::reset() {
	kaynine::AutoLock<> lock(guard_);

	//for (uint i = 0; i < MAX_RESOURCES; ++i) {
	//	resources_[i].path[0] = NULL;
	//	resources_[i].bufferPtr = NULL;
	//	resources_[i].statusPtr = NULL;
	//	resources_[i].status = Resource::Vacant;
	//}

	vacant_ = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint Resources::add(const TCHAR* const path, kaynine::MemoryPool* pool, void** const bufferPtr, uint* const sizePtr, bool* const statusPtr) {
	kaynine::AutoLock<> lock(guard_);

	assert(vacant_ < MAX_RESOURCES - 1 && path && bufferPtr && statusPtr);

	// initialize Resource	
	_tcsncpy(&resources_[vacant_].path[0], path, MAX_PATH);
	resources_[vacant_].pool = pool;
	resources_[vacant_].bufferPtr = bufferPtr;
	resources_[vacant_].sizePtr = sizePtr;
	resources_[vacant_].statusPtr = statusPtr;

	// reset resource status
	*resources_[vacant_].bufferPtr = NULL;
	*resources_[vacant_].sizePtr = 0;
	*resources_[vacant_].statusPtr = false;

	resources_[vacant_].status = Resource::Pending;

	newResource_.set();

	return vacant_++;
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::load(const uint item, const uint slot) {
	assert(item < MAX_RESOURCES && slot < SLOT_COUNT);

	TRACE_INFO(_T("loading '%s' in slot #%d"), resources_[item].path, slot);

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
		TRACE_ERROR(_T("couldn't open file '%s'"), resources_[item].path);
		return;
	}
	
	// file size
	const DWORD size = ::GetFileSize(file, NULL);
	if (!size) {
		::CloseHandle(file);

		resources_[item].status = Resource::Error;
		TRACE_ERROR(_T("couldn't load empty file '%s'"), resources_[item].path);
		return;
	}

	// allocate memory for file's contents
	void* const buffer = resources_[item].pool->allocate(size);
	assert(buffer);

	// prepare asio struct
	OVERLAPPED overlapped;
	memset(&overlapped, 0, sizeof(overlapped));

	assert(!events_.isSet(slot));
	overlapped.hEvent = events_.handle(slot);
	
	// initiate asio read
	DWORD read = 0;
	if (!::ReadFile(file, buffer, size, &read, &overlapped) && ::GetLastError() != ERROR_IO_PENDING) {
		::CloseHandle(file);
		TRACE_WARNING(_T("couldn't read empty file '%s'"), resources_[item].path);

		resources_[item].status = Resource::Error;
	} else {
		*resources_[item].bufferPtr = buffer;
		*resources_[item].sizePtr = size;
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
		TRACE_INFO(_T("checking for the new resources to load.."));
	else
		TRACE_INFO(_T("checking for the new resources to load in the slot #%d"), first);

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

	TRACE_INFO(_T("resource #%3d '%s' was successfully loaded in slot #%d"), slots_[slot].resource, resources_[slots_[slot].resource].path, slot);

	CHECKED_WINAPI_CALL(::CloseHandle(slots_[slot].file));
	events_.reset(slot, 1);

	*resources_[slots_[slot].resource].statusPtr = true;
	resources_[slots_[slot].resource].status = Resource::Done;
	
	slots_[slot].status = Slot::Vacant;
}

//---------------------------------------------------------------------------------------------------------------------
