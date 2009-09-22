#include "stdafx.h"

#include "utility/timer.h"
#include "video/video_system.h"

#include "profiler_screen_video.h"

using namespace engine;
using namespace game;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ProfilerScreenVideo::update(const float UNUSED(dt)) {
	static const float SECTION_STEP		= 2.0f;
	static const float BAR_HEIGHT		= 1.5f;
	static const float BAR_DEPTH		= 1.0f;

	static const float SCREEN_WIDTH		= 10.0f;
	static const float SCREEN_HEIGHT	= 10.0f;

	const float right	= float(Timer::inst().msec() / 100) / 10.f;	// the last full 0.1 sec tick
	const float left	= right - 0.1f;

	for (unsigned section = 0; section < Profiler::SECTION_COUNT; ++section) {
		for (int age = 0; age < ProfilerSections::HISTORY_DEPTH; ++age) {
			const Profiler::Period& period = Profiler::inst().get(section, -age);
			engine::MeshPtr& mesh = meshes_[section][age];

			if (!mesh)
				mesh = Video::inst().createMesh();

			const float begin	= (float)period.begin / 1000.f;
			const float end		= (float)period.end / 1000.f;

			if (left < begin && begin < right || left < end && end < right) {
				const float barLeft		= std::max(0.f, (begin - left) / 0.1f);
				const float barRight	= std::min((end - left) / 0.1f, 1.f);

				mesh->transform() = transformFromRect(barLeft, section * SECTION_STEP, barRight, section * SECTION_STEP + BAR_HEIGHT, BAR_DEPTH);
				mesh->draw(Video::inst().camera().view_projection());
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

