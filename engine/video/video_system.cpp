#include "stdafx.h"

#include "video_system.h"

#include "core/sync.h"
#include "window/window_system.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoSystem::VideoSystem() {
	Video::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystem::operator()() {
	kaynine::Event exitSignal(Sync::EXIT_SIGNAL_NAME);

	if (Window::get().create(800, 600, 32, 0, false) && Video::get().startup()) {
		while (!exitSignal.isSet()) {
			// TODO: valid dt here?
			Window::get().update(0);
			Video::get().update(0);
		}
	}

	Video::get().shutdown();
	Window::get().destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

