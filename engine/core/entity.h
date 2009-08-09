#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#include "utility/intrusive_ptr_base.h"
#include "utility/registry.h"
#include "utility/registry_index.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EntityBase : public IntrusivePtrBase {
public:
	EntityBase() : id_(RegistryIndex::inst().enlist())	{}
	~EntityBase()	{	RegistryIndex::inst().discharge(id_);	}

	const unsigned id() const	{	return id_;	}

private:
	const unsigned id_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TComponent1>
class Entity1 : public EntityBase {
public:
	Entity1()	{	Registry<TComponent1::Type>::add(id(), &component1_);	}

	~Entity1()	{	Registry<TComponent1::Type>::remove(id());	}

private:
	TComponent1 component1_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TComponent1, class TComponent2>
class Entity2 : public EntityBase {
public:
	Entity2()	{	Registry<TComponent1::Type>::add(id(), &component1_);
					Registry<TComponent2::Type>::add(id(), &component2_);	}

	~Entity2()	{	Registry<TComponent1::Type>::remove(id());
					Registry<TComponent2::Type>::remove(id());	}

private:
	TComponent1 component1_;
	TComponent2 component2_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TComponent1, class TComponent2, class TComponent3>
class Entity3 : public EntityBase {
public:
	Entity3()	{	Registry<TComponent1::Type>::add(id(), &component1_);
					Registry<TComponent2::Type>::add(id(), &component2_);
					Registry<TComponent3::Type>::add(id(), &component3_);	}

	~Entity3()	{	Registry<TComponent1::Type>::remove(id());
					Registry<TComponent2::Type>::remove(id());
					Registry<TComponent3::Type>::remove(id());	}

private:
	TComponent1 component1_;
	TComponent2 component2_;
	TComponent3 component3_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
