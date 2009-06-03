#include "stdafx.h"

#include "video/opengl/video_system_ogl.h"
#include "window/win32/window_w32.h"

#include "entities/orb/orb.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	engine::VideoSystemOGL video;
	engine::WindowSystemW32 window;

	game::Orb orb;

	boost::thread_group threads;
	threads.create_thread(boost::ref(engine::Video::get()));

	threads.join_all();

	// _getch();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

