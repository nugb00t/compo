#ifndef PROFILER_SCREEN_VIDEO_INCLUDED
#define PROFILER_SCREEN_VIDEO_INCLUDED

#include "core/profiler.h"
#include "video/video_component.h"
#include "video/mesh.h"

namespace game {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ProfilerScreenVideo : public engine::ScreenVideoComponent {
public:
	// interface: EntityVideoComponent
	virtual void update(const float dt);

private:
	engine::MeshPtr meshes_[engine::Profiler::SECTION_COUNT][engine::ProfilerSections::HISTORY_DEPTH];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
