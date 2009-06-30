#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#include "utility/intrusive_ptr_base.h"
#include "utility/registry.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EntityBase : public IntrusivePtrBase {
public:
	EntityBase() : id_(::rand())	{}

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
					Registry<TComponent1::Type>::remove(id());	}

private:
	TComponent1 component1_;
	TComponent2 component2_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
