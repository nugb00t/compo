#include "stdafx.h"

#include "engine.h"

#include "core/sync.h"
#include "filesystem/files.h"

#include "client/local_client_thread.h"
#include "filesystem/filesystem_thread.h"
#include "server/server_thread.h"
#include "video/video_thread.h"

#ifdef PLATFORM_WIN51
#include "system/win51/system_loop_w51.h"
#endif

using namespace engine;

namespace {
	static const uint CLIENT_PERIOD = 16;
	static const uint SERVER_PERIOD = 16;
	static const uint SERVER_DELAY = 4 * 10;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Engine::Engine(GameFactory& game) {
	Sync::inst();
	kaynine::Trace::inst();

	Files::inst();
	
	run(game);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Engine::run(GameFactory& game) {
#ifdef PLATFORM_WIN51
	SystemLoopW51 systemLoop;
#endif

	if (systemLoop.initialize()) {
		LocalClientThread localClient(game, systemLoop.controls());
		FileSystemThread fileSystem;
		ServerThread server(game);
		VideoThread video(game, systemLoop.window());

		HANDLE handles[] = {
			kaynine::PulseThread<Sync, CLIENT_PERIOD>::create(&localClient),
			kaynine::Thread<Sync>::create(&fileSystem),
			kaynine::PulseThread<Sync, SERVER_PERIOD, SERVER_DELAY>::create(&server),
			kaynine::Thread<Sync>::create(&video),
		};
		kaynine::Handles threads(&handles[0], sizeof(handles) / sizeof(HANDLE));

		while (!Sync::inst().exit.check() && systemLoop.update());

		Sync::inst().exit.set();
		threads.waitAll(); 

		systemLoop.terminate();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
