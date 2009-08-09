#ifndef VIDEO_COMPONENT_INCLUDED
#define VIDEO_COMPONENT_INCLUDED

#include "utility/intrusive_ptr_base.h"
#include "utility/registry.h"
#include "core/sync.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoComponent {
public:
	typedef engine::VideoComponent Type;

public:
	virtual void update(const Sync::EntityParams& fromLogic, const float dt) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef boost::intrusive_ptr<VideoComponent> VideoComponentPtr;

typedef Registry<VideoComponent, Sync::MAX_ENTITIES> VideoComponentRegistry;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
