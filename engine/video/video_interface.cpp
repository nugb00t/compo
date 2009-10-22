#include "stdafx.h"

#include "video_interface.h"

#include "core/core.h"
#include "core/sync.h"
#include "core/profiler.h"
#include "system/window_interface.h"
#include "video/video_component.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoInterface::VideoInterface() {
	Video::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoInterface::operator()() {
	if (Video::inst().startup()) {
		// TODO: move camera to its own entity
		camera_ = createCamera();
		assert(camera_);

		kaynine::WaitableTimer timer(unsigned(1000.f / FRAMERATE));
		kaynine::Event signal(EXIT_SIGNAL_NAME);
		kaynine::MultipleObjects objects(timer, signal);

		for (unsigned wait = WAIT_OBJECT_0; wait == WAIT_OBJECT_0; wait = objects.waitAny()) {
			assert(wait != WAIT_FAILED);
			Profiler::StopWatch stopWatch(Profiler::VIDEO_THREAD);
			Video::inst().update(0);
		}
	}

	Video::inst().shutdown();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoInterface::update(const unsigned msec) {
	clear();

	if (begin()) {
		camera_->update(msec);

		Sync::LogicToVideoReadable fromLogic(Sync::inst().logicToVideo());

		if (fromLogic)
			for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
				if (EntityVideoComponentRegistry::inst().valid(i))
					EntityVideoComponentRegistry::inst().get(i).update(fromLogic->entities[i], msec);

		for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
			if (ScreenVideoComponentRegistry::inst().valid(i))
				ScreenVideoComponentRegistry::inst().get(i).update(msec);

		end();
	}
	
	present();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

