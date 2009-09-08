#include "stdafx.h"

#include "video_system.h"

#include "core/core.h"
#include "core/sync.h"
#include "core/profiler.h"
#include "window/window_system.h"
#include "video/video_component.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoSystem::VideoSystem() {
	Video::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystem::operator()() {
	kaynine::Event exitSignal(EXIT_SIGNAL_NAME);

	if (Window::inst().create(800, 600, 32, 0, false) && Video::inst().startup()) {
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

				Window::inst().update(dt);
				Video::inst().update(dt);
			}

			timer.wait(unsigned(1000.f / FRAMERATE) * 2);
		}
	}

	Video::inst().shutdown();
	Window::inst().destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystem::update(const float dt) {
	clear();

	if (begin()) {
		camera_->update(dt);

		Sync::LogicToVideoReadable fromLogic(Sync::inst().logicToVideo());

		if (fromLogic)
			for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
				if (EntityVideoComponentRegistry::inst().valid(i))
					EntityVideoComponentRegistry::inst().get(i).update(fromLogic->entityParams[i], dt);

		for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
			if (ScreenVideoComponentRegistry::inst().valid(i))
				ScreenVideoComponentRegistry::inst().get(i).update(dt);

		end();
	}
	
	present();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

