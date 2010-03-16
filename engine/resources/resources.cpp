#include "stdafx.h"

#include "resources.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Resources::Resources() : vacant_(0), events_(handles_, sizeof(handles_) / sizeof(HANDLE), 2) {
	for (uint i = 0; i < SLOT_COUNT; ++i)
		slots_[i].status = Slot::Vacant;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::initialize() {
	handles_[0] = g_engine.sync->exit.handle();
	handles_[1] = newResource_.handle();

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::update() {
	assert(vacant_ < MAX_RESOURCES - 1);

	for (unsigned wait = events_.waitAny(); wait != WAIT_OBJECT_0 && wait != WAIT_FAILED && wait != WAIT_ABANDONED; wait = events_.waitAny())
		if (wait == WAIT_OBJECT_0 + 1) {	// new resource
			schedule();
			newResource_.reset();
		} else if (WAIT_IO_COMPLETION <= wait && wait < WAIT_IO_COMPLETION + SLOT_COUNT) {
			complete(WAIT_IO_COMPLETION - wait);
			schedule(WAIT_IO_COMPLETION - wait);
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

uint Resources::add(const TCHAR* const path, kaynine::MemoryPool* pool, void** const bufferPtr, bool* const statusPtr) {
	kaynine::AutoLock<> lock(guard_);

	assert(vacant_ < MAX_RESOURCES - 1 && path && bufferPtr && statusPtr);
	
	_tcsncpy(&resources_[vacant_].path[0], path, MAX_PATH);
	resources_[vacant_].pool = pool;
	resources_[vacant_].bufferPtr = bufferPtr;
	resources_[vacant_].statusPtr = statusPtr;
	resources_[vacant_].status = Resource::Pending;
	
	newResource_.set();

	return vacant_++;
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::load(const uint item, const uint slot) {
	assert(item < MAX_RESOURCES && slot < SLOT_COUNT);

	slots_[slot].resource = &resources_[item];

	TRACE_INFO(_T("loading '%s' in slot #%d"), resources_[item].path, slot);

	// open the file
	slots_[slot].file = ::CreateFile(resources_[item].path, 
									 GENERIC_READ, 
									 FILE_SHARE_READ, 
									 NULL, 
									 OPEN_EXISTING, 
									 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN,
									 NULL);
	if (slots_[slot].file == INVALID_HANDLE_VALUE) {
		resources_[item].status = Resource::Error;
		TRACE_ERROR(_T("couldn't open file '%s'"), resources_[item].path);
	}
	
	uint size = ::GetFileSize(slots_[slot].file, NULL);
	if (!size) {
		::CloseHandle(slots_[slot].file);

		resources_[item].status = Resource::Error;
		TRACE_ERROR(_T("couldn't load empty file '%s'"), resources_[item].path);
	}

	*resources_[item].bufferPtr = resources_[item].pool->allocate(size);
	*resources_[item].statusPtr = false;
	assert(*resources_[item].bufferPtr);

	memset(&slots_[slot].overlapped, 0, sizeof(slots_[slot].overlapped));
	assert(!events_.isSet(slot + 1));
	slots_[slot].overlapped.hEvent = events_.handle(slot + 1);
	
	// initiate asio read
	if (!::ReadFileEx(slots_[slot].file, NULL, size, &slots_[slot].overlapped, NULL)) {
		::CloseHandle(slots_[slot].file);

		resources_[item].status = Resource::Error;
		TRACE_ERROR(_T("couldn't read empty file '%s'"), resources_[item].path);
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
				load(item, slot);
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::complete(const unsigned slot) {
	assert(slots_[slot].status == Slot::Processing);

	TRACE_INFO(_T("checking for the new resources to load.."));

	CHECKED_WINAPI_CALL(::CloseHandle(slots_[slot].file));
	events_.reset(slot, 1);

	slots_[slot].resource->status = Resource::Done;
	*slots_[slot].resource->statusPtr = true;
	slots_[slot].status = Slot::Vacant;
}

//---------------------------------------------------------------------------------------------------------------------
