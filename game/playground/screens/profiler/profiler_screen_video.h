#ifndef PROFILER_SCREEN_VIDEO_INCLUDED
#define PROFILER_SCREEN_VIDEO_INCLUDED

#include "core/profiler.h"
#include "video/video_component.h"
#include "video/mesh.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ProfilerScreenVideo : public engine::ScreenVideoComponent {
public:
    ProfilerScreenVideo();

	// interface: VideoComponent
	virtual void update(const unsigned msec);

private:
	engine::MeshPtr meshes_[engine::Profiler::SECTION_COUNT][engine::ProfilerSections::HISTORY_DEPTH];
    engine::EffectPtr effect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
