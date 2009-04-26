#ifndef ORB_VIDEO_INCLUDED
#define ORB_VIDEO_INCLUDED

#include "video/video_component.h"

namespace game {

//=====================================================================================================================

class OrbVideo : public engine::VideoComponent {
public:
	// interface: Updatable
	virtual void update(const float dt);
};

//=====================================================================================================================

}

#endif
