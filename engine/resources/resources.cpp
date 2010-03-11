#include "stdafx.h"

#include "resources.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::update() {
	kaynine::AutoLock<> lock(guard_);

	// go through the resource_ array and schedule file read if there's a vacant place in the queue
	for (uint slot = 0, item = 0; slot < MAX_LOADS && item < MAX_RESOURCES; ++slot) {
		if (loads_[slot].status != Load::VACANT)
			continue;
		
		while (resources_[item].status != Resource::PENDING && item < MAX_RESOURCES)
			++item;
		
		load(resources_[item], loads_[slot]);
	}
	
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint Resources::add(const TCHAR* const path, void** const bufferPtr, bool** const statusPtr) {
	kaynine::AutoLock<> lock(guard_);

	assert(vacantResource_ < MAX_RESOURCES - 1 && path && bufferPtr && statusPtr);
	
	_tcsncpy(&resources_[vacantResource_].path[0], path, MAX_PATH);
	resources_[vacantResource_].bufferPtr = bufferPtr;
	resources_[vacantResource_].statusPtr = statusPtr;
	
	return vacantResource_++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Resources::reset() {
	for (uint i = 0; i < MAX_RESOURCES; ++i) {
		resources_[i].path[0] = NULL;
		resources_[i].bufferPtr = NULL;
		resources_[i].statusPtr = NULL;
		resources_[i].status = Resource::VACANT;
	}

	for (uint i = 0; i < MAX_LOADS; ++i)
		loads_[i].status = Load::VACANT;
	
	vacantResource_ = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Resources::load(const Resource& item, Load& slot) {
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
	
	// set up overlapped struct
	memset(&slot.overlapped, 0, sizeof(slot.overlapped));
	slot.overlapped.hEvent = &slot;
	
	// initiate asio read
	CHECKED_WINAPI_CALL(::ReadFileEx(file, NULL, size, &slot.overlapped, NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
