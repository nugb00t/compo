#ifndef REGISTRANT_INCLUDED
#define REGISTRANT_INCLUDED

#include "intrusive_ptr_base.h"
#include "registry.h"
#include "registry_index.h"

#include "core/sync.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RegistrantBase : public IntrusivePtrBase {
public:
	RegistrantBase() : id_(RegistryIndex::inst().enlist())	{}
	~RegistrantBase()	{	RegistryIndex::inst().dismiss(id_);	}

	const unsigned id() const	{	return id_;	}

private:
	const unsigned id_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TComponent1>
class Registrant1 : public RegistrantBase {
public:
	Registrant1()	{	Registry<TComponent1::Type, Sync::MAX_ENTITIES>::inst().add(id(), &component1_);	}

	~Registrant1()	{	Registry<TComponent1::Type, Sync::MAX_ENTITIES>::inst().remove(id());	}

private:
	TComponent1 component1_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TComponent1, class TComponent2>
class Registrant2 : public RegistrantBase {
public:
	Registrant2()	{	Registry<TComponent1::Type, Sync::MAX_ENTITIES>::inst().add(id(), &component1_);
						Registry<TComponent2::Type, Sync::MAX_ENTITIES>::inst().add(id(), &component2_);	}

	~Registrant2()	{	Registry<TComponent1::Type, Sync::MAX_ENTITIES>::inst().remove(id());
						Registry<TComponent2::Type, Sync::MAX_ENTITIES>::inst().remove(id());	}

private:
	TComponent1 component1_;
	TComponent2 component2_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TComponent1, class TComponent2, class TComponent3>
class Registrant3 : public RegistrantBase {
public:
	Registrant3()	{	Registry<TComponent1::Type, Sync::MAX_ENTITIES>::inst().add(id(), &component1_);
						Registry<TComponent2::Type, Sync::MAX_ENTITIES>::inst().add(id(), &component2_);
						Registry<TComponent3::Type, Sync::MAX_ENTITIES>::inst().add(id(), &component3_);	}

	~Registrant3()	{	Registry<TComponent1::Type, Sync::MAX_ENTITIES>::inst().remove(id());
						Registry<TComponent2::Type, Sync::MAX_ENTITIES>::inst().remove(id());
						Registry<TComponent3::Type, Sync::MAX_ENTITIES>::inst().remove(id());	}

private:
	TComponent1 component1_;
	TComponent2 component2_;
	TComponent3 component3_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
