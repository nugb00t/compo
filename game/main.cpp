#include "stdafx.h"

#include "video/directx/video_system_dx.h"
#include "window/win32/window_system_w32.h"

#define TEST

#ifdef TEST
#include "video/video_system.h"
#include "window/window_system.h"
#endif

#include "entities/orb/orb.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	DEBUG_ONLY(bool ok = )
		kaynine::setCurrentDirectory();
	assert(ok);

	engine::VideoSystemDX video;
	engine::WindowSystemW32 window;

	boost::thread_group threads;
	threads.create_thread(boost::ref(engine::Video::get()));

	game::Orb orb;

	threads.join_all();

	// _getch();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

