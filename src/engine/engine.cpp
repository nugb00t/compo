#include "stdafx.h"

#include "engine.h"

#include "filesystem/filesystem_thread.h"
#include "server/server_thread.h"
#include "video/video_thread.h"

#ifdef PLATFORM_WIN51
#include "system/win51/system_loop_w51.h"
#endif

#include "filesystem/resources.h"

using namespace engine;

namespace {
	static const uint SERVER_PERIOD = 16;
	static const uint SERVER_DELAY = 4 * 10;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Engine::Engine(Game* game) :
#ifdef PLATFORM_WIN51
	inputW51(new InputW51),
	input(inputW51.get()), 
	windowW51(new WindowW51),
	window(windowW51.get()),
#endif
#ifdef VIDEO_DIRECT3D9
	videoD3D9(new VideoD3D9), 
	video(videoD3D9.get()), 
#endif
	localClient(new LocalClient(game->localClient.get())),
	profiler(new Profiler),
	time(new Time),
	game_(game)
{
	kaynine::Holder<Engine>::set(this);

	// singleton initializations
	Sync::inst();
	kaynine::Trace::inst();

	Resources::inst();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Engine::run() {
	FileSystemThread fileSystem;
	ServerThread server(*game_->arbiter, *game_->logicFactory);
	VideoThread video(*video, *game_->video, *game_->videoFactory, *game_->screenVideoFactory);
#ifdef PLATFORM_WIN51
	SystemLoopW51 systemLoop;
#endif

	HANDLE handles[] = {
		kaynine::Thread<Sync>::create(&fileSystem),
		kaynine::PulseThread<Sync, SERVER_PERIOD, SERVER_DELAY>::create(&server),
		kaynine::Thread<Sync>::create(&video),
		kaynine::Thread<Sync>::create(&systemLoop),
	};
	kaynine::Handles threads(&handles[0], sizeof(handles) / sizeof(HANDLE));
	threads.waitAll(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
