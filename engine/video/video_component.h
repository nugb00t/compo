#ifndef VIDEO_COMPONENT_INCLUDED
#define VIDEO_COMPONENT_INCLUDED

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EntityVideoComponent {
public:
	typedef engine::EntityVideoComponent Type;

public:
    virtual void update(const ServerState::Entity& fromLogic, const unsigned msec) = 0;
};

typedef boost::intrusive_ptr<EntityVideoComponent> EntityVideoComponentPtr;

typedef kaynine::Index<ServerState::MAX_ENTITIES>::Registry<EntityVideoComponent> EntityVideoComponentRegistry;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreenVideoComponent {
public:
	typedef engine::ScreenVideoComponent Type;

public:
	virtual void update(const unsigned msec) = 0;
};

typedef boost::intrusive_ptr<ScreenVideoComponent> ScreenVideoComponentPtr;

typedef kaynine::Index<ServerState::MAX_ENTITIES>::Registry<ScreenVideoComponent> ScreenVideoComponentRegistry;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
