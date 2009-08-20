#include "stdafx.h"

#include "registry_index.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RegistryIndex::RegistryIndex()
: firstFree_(0), size_(0), guard_(kaynine::CriticalSection::UNLOCKED) {
	for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
		ids_[i] = i + 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned RegistryIndex::enlist() {
	assert(size_ <= Sync::MAX_ENTITIES);

	kaynine::AutoLock<> lock(guard_);

	const unsigned ret = firstFree_;
	firstFree_ = ids_[ret];
	ids_[ret] = TAKEN;

	++size_;

	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RegistryIndex::dismiss(const unsigned id) {
	assert(id <= Sync::MAX_ENTITIES);
	assert(size_ >= 0);

	kaynine::AutoLock<> lock(guard_);

	ids_[id] = firstFree_;
	firstFree_ = id;

	--size_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
