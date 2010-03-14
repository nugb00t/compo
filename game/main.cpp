#include "stdafx.h"

#include "engine.h"
#include "game.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int __cdecl _tmain(int UNUSED(argc), _TCHAR* UNUSED(argv[])) {
	CHECKED_CALL(kaynine::setCurrentDirectory());

	HANDLE handles[] = {
		kaynine::Thread<Sync>::create(g_engine.systemLoop),
		kaynine::PulseThread<Sync>::create(g_engine.resources.get()),
		kaynine::PulseThread<Sync>::create(g_engine.server.get()),
		kaynine::PulseThread<Sync>::create(g_game.video.get())
	};
	kaynine::Handles threads(&handles[0], sizeof(handles) / sizeof(HANDLE));

	// synchronize thread start
	Sync::start.set();

	threads.waitAll();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
