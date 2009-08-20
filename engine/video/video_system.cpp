#include "stdafx.h"

#include "video_system.h"

#include "core/core.h"
#include "core/sync.h"
#include "core/profiler.h"
#include "window/window_system.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoSystem::VideoSystem() {
	Video::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystem::operator()() {
	kaynine::Event exitSignal(EXIT_SIGNAL_NAME);

	if (Window::inst().create(800, 600, 32, 0, false) && Video::inst().startup()) {
		kaynine::WaitableTimer timer(unsigned(1000.f / FRAMERATE));

		unsigned long last = Timer::inst().now();

		while (!exitSignal.isSet()) {
			const float dt = static_cast<float>(Timer::inst().now() - last) / 1000.f;
			last = Timer::inst().now();

			{
				Profiler::StopWatch stopWatch(Profiler::LOGIC_THREAD);

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

