#include "stdafx.h"

#include "engine.h"

#include "filesystem/filesystem_thread.h"
#include "server/server_thread.h"
#include "video/video_thread.h"

#ifdef PLATFORM_WIN51
#include "system/win51/system_loop_w51.h"
#endif

using namespace engine;

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
	resources(new Resources),
	game_(game)
{
	kaynine::Holder<Engine>::set(this);

	Sync::inst();
	kaynine::Trace::inst();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Engine::run() {
	FileSystemThread fileSystem;
	ServerThread server(game_->arbiter.get(), game_->logicFactory.get());
	VideoThread video(video, game_->video.get(), game_->videoFactory.get(), game_->screenVideoFactory.get());
#ifdef PLATFORM_WIN51
	SystemLoopW51 systemLoop;
#endif

	HANDLE handles[] = {
		kaynine::Thread<Sync>::create(&fileSystem),
		kaynine::PulseThread<Sync>::create(&server),
		kaynine::PulseThread<Sync>::create(&video),
		kaynine::Thread<Sync>::create(&systemLoop),
	};

	kaynine::Handles threads(&handles[0], sizeof(handles) / sizeof(HANDLE));
	threads.waitAll(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
