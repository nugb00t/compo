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
	kaynine::Event exitSignal(sync::EXIT_SIGNAL_NAME);

	if (Window::get().create(800, 600, 32, 0, false) && Video::get().startup()) {
		kaynine::WaitableTimer timer(sync::VIDEO_FRAMETIME);

		time_t last = Core::inst().time();
		float dt;

		while (!exitSignal.isSet()) {
			dt = static_cast<float>(Core::inst().time() - last);
			last = Core::inst().time();

			Window::get().update(dt);
			Video::get().update(dt);

			timer.wait(sync::VIDEO_FRAMETIME * 2);
		}
	}

	Video::get().shutdown();
	Window::get().destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

