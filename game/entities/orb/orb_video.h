#ifndef ORB_VIDEO_INCLUDED
#define ORB_VIDEO_INCLUDED

#include "video/video_component.h"
#include "video/mesh.h"
#include "video/texture.h"

namespace game {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbVideo : public engine::EntityVideoComponent {
public:
	// interface: EntityVideoComponent
	virtual void update(const engine::Drawn::Params& fromLogic, const float dt);

private:
	engine::MeshPtr mesh_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
