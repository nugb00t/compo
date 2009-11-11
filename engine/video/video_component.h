#ifndef VIDEO_COMPONENT_INCLUDED
#define VIDEO_COMPONENT_INCLUDED

#include "server/server_view.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EntityVideoComponent {
public:
	typedef engine::EntityVideoComponent Type;

public:
    virtual void update(const ServerView::Entity& fromLogic, const unsigned msec) = 0;
};

typedef boost::intrusive_ptr<EntityVideoComponent> EntityVideoComponentPtr;

typedef kaynine::Index<ServerView::MAX_ENTITIES>::Registry<EntityVideoComponent> EntityVideoComponentRegistry;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreenVideoComponent {
public:
	typedef engine::ScreenVideoComponent Type;

public:
	virtual void update(const unsigned msec) = 0;
};

typedef boost::intrusive_ptr<ScreenVideoComponent> ScreenVideoComponentPtr;

typedef kaynine::Index<ServerView::MAX_ENTITIES>::Registry<ScreenVideoComponent> ScreenVideoComponentRegistry;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
