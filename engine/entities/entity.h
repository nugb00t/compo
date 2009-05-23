#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#include "utility/registry.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoComponentEmpty {};
class AudioComponentEmpty {};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TVideoComponent = VideoComponentEmpty, class TAudioComponent = AudioComponentEmpty>
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
	Registry<VideoComponent>::add(id_, &videoComponent_);
	Registry<AudioComponent>::add(id_, &audioComponent_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TVideoComponent, class TAudioComponent>
Entity<TVideoComponent, TAudioComponent>::~Entity() {
	Registry<VideoComponent>::remove(id_);
	Registry<AudioComponent>::remove(id_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
