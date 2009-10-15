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
	kaynine::Event exitSignal(EXIT_SIGNAL_NAME);

	if (Video::inst().startup()) {
		// TODO: move camera to its own entity
		camera_ = createCamera();
		assert(camera_);

		kaynine::WaitableTimer timer(unsigned(1000.f / FRAMERATE));

		unsigned long last = Timer::inst().msec();

		while (!exitSignal.isSet()) {
			const float dt = static_cast<float>(Timer::inst().msec() - last) / 1000.f;
			last = Timer::inst().msec();

			{
				Profiler::StopWatch stopWatch(Profiler::VIDEO_THREAD);

				Video::inst().update(dt);
			}

			timer.wait(unsigned(1000.f / FRAMERATE) * 2);
		}
	}

	Video::inst().shutdown();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoInterface::update(const float dt) {
	clear();

	if (begin()) {
		camera_->update(dt);

		Sync::LogicToVideoReadable fromLogic(Sync::inst().logicToVideo());

		if (fromLogic)
			for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
				if (EntityVideoComponentRegistry::inst().valid(i))
					EntityVideoComponentRegistry::inst().get(i).update(fromLogic->entities[i], dt);

		for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
			if (ScreenVideoComponentRegistry::inst().valid(i))
				ScreenVideoComponentRegistry::inst().get(i).update(dt);

		end();
	}
	
	present();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

