#include "stdafx.h"

#include "video_system.h"

#include "core/core.h"
#include "core/sync.h"
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

		time_t last = Core::inst().time();
		float dt;

		while (!exitSignal.isSet()) {
			dt = static_cast<float>(Core::inst().time() - last);
			last = Core::inst().time();

			Window::inst().update(dt);
			Video::inst().update(dt);

			timer.wait(unsigned(1000.f / FRAMERATE) * 2);
		}
	}

	Video::inst().shutdown();
	Window::inst().destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

