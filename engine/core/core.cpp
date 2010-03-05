#include "stdafx.h"

#include "core.h"
#ifdef PLATFORM_WIN51
	#include "system/win51/system_loop_w51.h"
#endif

#include "engine.h"
#include "game.h"
#include "profiler.h"

// thread classes
#include "server/server.h"
#include "resources/resources.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::Core() 
:   threads_(
		kaynine::Thread<Sync>::create(
#ifdef PLATFORM_WIN51
			new SystemLoopW51
#endif
		),
		kaynine::PulseThread<Sync>::create(new Resources),
		kaynine::PulseThread<Sync>::create(new Server),
		kaynine::PulseThread<Sync>::create(g_game.video.get())
        )
{
	// synchronize thread start
	Sync::start.set();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::~Core() {
    threads_.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
