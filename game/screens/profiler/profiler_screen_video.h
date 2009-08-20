#ifndef PROFILER_SCREEN_VIDEO_INCLUDED
#define PROFILER_SCREEN_VIDEO_INCLUDED

#include "video/video_component.h"
#include "video/mesh.h"

namespace game {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ProfilerScreenVideo : public engine::ScreenVideoComponent {
public:
	// interface: EntityVideoComponent
	virtual void update(const float dt);

private:
	engine::MeshPtr mesh_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
