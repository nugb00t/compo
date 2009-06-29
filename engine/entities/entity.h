#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#include "utility/registry.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TVideoComponent = Empty, class TAudioComponent = Empty>
class Entity {
	const unsigned id_;

public:
	Entity();
	~Entity();

	const unsigned id() const { return id_; }

protected:
	TVideoComponent videoComponent_;
	TAudioComponent audioComponent_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TVideoComponent, class TAudioComponent>
Entity<TVideoComponent, TAudioComponent>::Entity()
: id_(::rand())
{
	registerComponent<TVideoComponent>(id_, &videoComponent_);
	registerComponent<TAudioComponent>(id_, &audioComponent_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TVideoComponent, class TAudioComponent>
Entity<TVideoComponent, TAudioComponent>::~Entity() {
	unregisterComponent<TVideoComponent>(id_);
	unregisterComponent<TAudioComponent>(id_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
