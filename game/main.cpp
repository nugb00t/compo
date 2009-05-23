#include "stdafx.h"

#include "video/opengl/video_system_ogl.h"

#include "entities/orb/orb.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	engine::VideoSystemOGL video;

	game::Orb orb;

	boost::thread_group threads;
	threads.create_thread(boost::ref(video));

	threads.join_all();

	// _getch();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

