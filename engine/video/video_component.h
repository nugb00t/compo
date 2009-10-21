#ifndef VIDEO_COMPONENT_INCLUDED
#define VIDEO_COMPONENT_INCLUDED

#include "utility/registry.h"
#include "core/sync.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EntityVideoComponent {
public:
	typedef engine::EntityVideoComponent Type;

public:
	virtual void update(const Entity::Params& fromLogic, const unsigned msec) = 0;
};

typedef boost::intrusive_ptr<EntityVideoComponent> EntityVideoComponentPtr;

typedef Registry<EntityVideoComponent, Sync::MAX_ENTITIES> EntityVideoComponentRegistry;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreenVideoComponent {
public:
	typedef engine::ScreenVideoComponent Type;

public:
	virtual void update(const unsigned msec) = 0;
};

typedef boost::intrusive_ptr<ScreenVideoComponent> ScreenVideoComponentPtr;

typedef Registry<ScreenVideoComponent, Sync::MAX_ENTITIES> ScreenVideoComponentRegistry;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
