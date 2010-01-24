#ifndef THREAD_PROFILER_VIDEO_INCLUDED
#define THREAD_PROFILER_VIDEO_INCLUDED

#include "core/profiler.h"
#include "video/video_component.h"

#include "video/effect.h"
#include "video/mesh.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ThreadProfilerVideo : public engine::ScreenVideoComponent {
public:
    ThreadProfilerVideo() : effect_(NULL), mesh_(NULL) {}

	// interface: VideoComponent
	virtual void draw();

private:
	engine::EffectPtr effect_;
	engine::MeshPtr mesh_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
