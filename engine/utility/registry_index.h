#ifndef REGISTRY_INDEX_INCLUDED
#define REGISTRY_INDEX_INCLUDED

#include "core/sync.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RegistryIndex : public kaynine::Singleton<RegistryIndex> {
	static const unsigned TAKEN = (unsigned)-1;

protected:
	RegistryIndex();

public:
	const unsigned enlist();
	void dismiss(const unsigned id);

	const unsigned size() const { return size_; }

private:
	unsigned ids_[Sync::MAX_ENTITIES];
	unsigned firstFree_;
	unsigned size_;

	kaynine::CriticalSection guard_;

	friend struct kaynine::Singleton<RegistryIndex>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif