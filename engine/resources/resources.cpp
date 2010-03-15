#include "stdafx.h"

#include "resources.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::initialize() {
	handles_[0] = g_engine.sync->exit.handle();
	handles_[1] = newResource_.handle();

	reset();

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

	for (uint i = 0; i < MAX_RESOURCES; ++i) {
		resources_[i].path[0] = NULL;
		resources_[i].bufferPtr = NULL;
		resources_[i].statusPtr = NULL;
		resources_[i].status = Resource::VACANT;
	}

	for (uint i = 0; i < SLOT_COUNT; ++i)
		slots_[i].status = Slot::VACANT;
	
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
	
	newResource_.set();

	return vacant_++;
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::load(const uint item, const uint slot) {
	slots_[slot].resource = &resources_[item];

	// open the file
	slots_[slot].file = ::CreateFile(resources_[item].path, 
							 GENERIC_READ, 
							 FILE_SHARE_READ, 
							 NULL, 
							 OPEN_EXISTING, 
							 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN,
							 NULL);
	assert(slots_[slot].file != INVALID_HANDLE_VALUE);
	
	uint size = ::GetFileSize(slots_[slot].file, NULL);
	assert(size);

	*resources_[item].bufferPtr = resources_[item].pool->allocate(size);
	*resources_[item].statusPtr = false;
	assert(*resources_[item].bufferPtr);

	memset(&slots_[slot].overlapped, 0, sizeof(slots_[slot].overlapped));
	assert(!events_.isSet(slot + 1));
	slots_[slot].overlapped.hEvent = events_.handle(slot + 1);
	
	// initiate asio read
	CHECKED_WINAPI_CALL(::ReadFileEx(slots_[slot].file, NULL, size, &slots_[slot].overlapped, NULL));
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::schedule(const unsigned first /*= 0*/) {
	assert(first < SLOT_COUNT);

	for (uint slot = first, item = 0; slot < SLOT_COUNT && item < vacant_; ++slot) {
		if (slots_[slot].status == Slot::VACANT) {
			while (resources_[item].status != Resource::PENDING && item < MAX_RESOURCES)
				++item;

			load(item, slot);
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::complete(const unsigned slot) {
	assert(slots_[slot].status == Slot::PROCESSING);

	CHECKED_WINAPI_CALL(::CloseHandle(slots_[slot].file));
	events_.reset(slot, 1);

	slots_[slot].resource->status = Resource::DONE;
	*slots_[slot].resource->statusPtr = true;
	slots_[slot].status = Slot::VACANT;
}

//---------------------------------------------------------------------------------------------------------------------
