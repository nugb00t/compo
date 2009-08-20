#include "stdafx.h"

#include "video/video_system.h"
#include "core/profiler.h"

#include "profiler_screen_video.h"

using namespace engine;
using namespace game;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ProfilerScreenVideo::update(const float UNUSED(dt)) {
	if (!mesh_)
		mesh_ = Video::inst().createMesh();

	const Profiler::Period& period_3 = Profiler::inst().get(Profiler::VIDEO_THREAD, -3);
	const float left_3 = 1.f + (float)period_3.middle() / 1000.f - (float)period_3.start / 1000.f;
	const float length_3 = (float)period_3.length() / 1000.f;
	mesh_->draw(
		Vector3(left_3, 2.f, 1.0f),	
		Vector3(0.f, 0.f, 0.f),	
		Vector3(length_3, .2f, 0.f));

	const Profiler::Period& period_2 = Profiler::inst().get(Profiler::VIDEO_THREAD, -2);
	const float left_2 = 1.f + (float)period_2.middle() / 1000.f - (float)period_3.start / 1000.f;
	const float length_2 = (float)period_2.length() / 1000.f;
	mesh_->draw(
		Vector3(left_2, 2.f, 1.0f),	
		Vector3(0.f, 0.f, 0.f),	
		Vector3(length_2, .2f, 0.f));

	const Profiler::Period& period_1 = Profiler::inst().get(Profiler::VIDEO_THREAD, -1);
	const float left_1 = 1.f + (float)period_1.middle() / 1000.f - (float)period_3.start / 1000.f;
	const float length_1 = (float)period_1.length() / 1000.f;
	mesh_->draw(
		Vector3(left_1, 2.f, 1.0f),	
		Vector3(0.f, 0.f, 0.f),	
		Vector3(length_1, .2f, 0.f));

	const Profiler::Period& period_0 = Profiler::inst().get(Profiler::VIDEO_THREAD);
	const float left_0 = 1.f + (float)period_0.middle() / 1000.f - (float)period_3.start / 1000.f;
	const float length_0 = (float)period_0.length() / 1000.f;
	mesh_->draw(
		Vector3(left_0, 2.f, 1.0f),	
		Vector3(0.f, 0.f, 0.f),	
		Vector3(length_0, .2f, 0.f));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

