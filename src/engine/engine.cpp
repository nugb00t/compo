#include "stdafx.h"

#include "engine.h"

#include "filesystem/filesystem_thread.h"
#include "server/server_thread.h"
#include "video/video_thread.h"

#ifdef PLATFORM_WIN51
#include "system/win51/system_loop_w51.h"
#endif

#include "filesystem/resources.h"

// TEMP
#include <kaynine/containers/static_list.h>
// TEMP

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

	// TEMP
	//kaynine::MemoryPool pool(1024);
	//const uint index = Resources::inst().add(_T("main/fonts/bureau_20_o_0.dds"), pool);
	//const Resource& item = Resources::inst().get(index);

	//while (item.status == Resource::Pending || item.status == Resource::Processing) {
	//	Sleep(1000);
	//	Resources::inst().update();
	//}

	//pool.deallocate(item.buffer);
	// TEMP

	// TEMP
	kaynine::StaticList<uint, 4> list;
	uint i0 = list.add(0); assert(i0 == 0);
	uint i1 = list.add(1); assert(i1 == 1);
	list.remove(i0);

	uint i2 = list.add(0); assert(i2 == 0);
	uint i3 = list.add(2); assert(i3 == 2);

	list.reset();
	// TEMP
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
