#ifndef REGISTRY_INDEX_INCLUDED
#define REGISTRY_INDEX_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RegistryIndex : public kaynine::Singleton<RegistryIndex> {
public:
	static const unsigned SIZE = 4096;

private:
	static const unsigned TAKEN = (unsigned)-1;

protected:
	RegistryIndex();

public:
	const unsigned enlist();
	void discharge(const unsigned id);

	const unsigned size() const { return size_; }

private:
	unsigned ids_[SIZE];
	unsigned firstFree_;
	unsigned size_;

	kaynine::CriticalSection lock_;

	friend struct kaynine::Singleton<RegistryIndex>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif