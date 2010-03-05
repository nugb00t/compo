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
		kaynine::Thread::create(
#ifdef PLATFORM_WIN51
			new SystemLoopW51
#endif
		),
		kaynine::PulseThread::create(new Resources),
		kaynine::PulseThread::create(new Server),
		kaynine::PulseThread::create(g_game.video.get())
        ) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::~Core() {
    threads_.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
