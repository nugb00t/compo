#include "stdafx.h"

#include "core.h"

#include "video/directx/video_system_dx.h"
#include "window/win32/window_system_w32.h"

using namespace engine;

void Core::run() {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	engine::VideoSystemDX video;
	engine::WindowSystemW32 window;

	boost::thread_group threads;
	threads.create_thread(boost::ref(engine::Video::get()));

	threads.join_all();
}