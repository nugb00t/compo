#ifndef ORB_VIDEO_INCLUDED
#define ORB_VIDEO_INCLUDED

#include "video/video_component.h"
#include "video/mesh.h"
#include "video/texture.h"

namespace game {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbVideo : public engine::VideoComponent {
public:
	typedef engine::VideoComponent Type;

	OrbVideo();

	// interface: Updatable
	virtual bool update(const float dt);

private:
	engine::MeshPtr mesh_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
