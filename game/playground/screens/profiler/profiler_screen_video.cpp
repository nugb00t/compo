#include "stdafx.h"

#include "utility/timer.h"
#include "video/video_interface.h"

#include "profiler_screen_video.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ProfilerScreenVideo::ProfilerScreenVideo()
:effect_(NULL) {
    for (unsigned i = 0; i < engine::Profiler::SECTION_COUNT; ++i)
        for (unsigned j = 0; j < engine::ProfilerSections::HISTORY_DEPTH; ++j)
            meshes_[i][j] = NULL;
}

void ProfilerScreenVideo::update(const float UNUSED(dt)) {
	static const float SECTION_STEP		= 2.0f;
	static const float BAR_HEIGHT		= 1.5f;
	static const float BAR_DEPTH		= 1.0f;

	static const float SCREEN_WIDTH		= 10.0f;
	static const float SCREEN_HEIGHT	= 10.0f;

	const float right	= float(Time::inst().msec() / 100) / 10.f;	// the last full 0.1 sec tick
	const float left	= right - 0.1f;

	for (unsigned section = 0; section < Profiler::SECTION_COUNT; ++section) {
		for (int age = 0; age < ProfilerSections::HISTORY_DEPTH; ++age) {
			const Profiler::Period& period = Profiler::inst().get(section, -age);
			engine::MeshPtr& mesh = meshes_[section][age];

			if (!mesh)
                effect_ = Video::inst().createEffect(_T("playground/fx/simple.h"), Video::inst().getVertexDecl(VertexDecl::POS_DIFFUSE_TEX));
				mesh = Video::inst().createMesh(effect_);
                
                Video::inst().createTexture(_T("playground/textures/myself.bmp"))
				));

			const float begin	= (float)period.begin / 1000.f;
			const float end		= (float)period.end / 1000.f;

			if (left < begin && begin < right || left < end && end < right) {
				const float barLeft		= std::max(0.f, (begin - left) / 0.1f);
				const float barRight	= std::min((end - left) / 0.1f, 1.f);

                Matrix44 transform = transformFromRect(barLeft, section * SECTION_STEP, barRight, section * SECTION_STEP + BAR_HEIGHT, BAR_DEPTH);
                transform *= Video::inst().camera().view_projection();
				mesh->draw(transform);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

