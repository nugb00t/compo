#include "stdafx.h"

#include "resources.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::update() {
	assert(vacant_ < MAX_RESOURCES - 1);

	for (uint slot = 0, item = 0; slot < SLOT_COUNT && item < vacant_; ++slot) {
		if (slots_[slot].status == Slot::VACANT) {
			while (resources_[item].status != Resource::PENDING && item < MAX_RESOURCES)
				++item;

			load(resources_[item], slots_[slot]);
		} else if (slots_[slot].status == Slot::PROCESSING && slots_[slot].event.wait(0) == WAIT_IO_COMPLETION) {
			slots_[slot].event.reset();
			slots_[slot].resource->status = Resource::DONE;
			*slots_[slot].resource->statusPtr = true;
			slots_[slot].status = Slot::VACANT;
		}
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

uint Resources::add(const TCHAR* const path, void* const bufferPtr, bool* const statusPtr) {
	kaynine::AutoLock<> lock(guard_);

	assert(vacant_ < MAX_RESOURCES - 1 && path && bufferPtr && statusPtr);
	
	_tcsncpy(&resources_[vacant_].path[0], path, MAX_PATH);
	resources_[vacant_].bufferPtr = bufferPtr;
	resources_[vacant_].statusPtr = statusPtr;
	
	return vacant_++;
}

//---------------------------------------------------------------------------------------------------------------------

void Resources::load(Resource& item, Slot& slot) {
	// open the file
	HANDLE file = ::CreateFile(item.path, 
							   GENERIC_READ, 
							   FILE_SHARE_READ, 
							   NULL, 
							   OPEN_EXISTING, 
							   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN,
							   NULL);
	assert(file);
	
	uint size = ::GetFileSize(file, NULL);
	assert(size);

	slot.resource = &item;
	// set up overlapped struct
	memset(&slot.overlapped, 0, sizeof(slot.overlapped));
	slot.overlapped.hEvent = slot.event.handle();
	
	// initiate asio read
	CHECKED_WINAPI_CALL(::ReadFileEx(file, NULL, size, &slot.overlapped, NULL));
}

//---------------------------------------------------------------------------------------------------------------------
