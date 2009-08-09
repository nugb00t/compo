#ifndef ORB_VIDEO_INCLUDED
#define ORB_VIDEO_INCLUDED

#include "video/video_component.h"
#include "video/mesh.h"
#include "video/texture.h"

namespace game {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbVideo : public engine::VideoComponent {
public:
	// interface: VideoComponent
	virtual void update(const engine::Sync::EntityParams& fromLogic, const float dt);

private:
	engine::MeshPtr mesh_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
