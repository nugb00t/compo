#include "stdafx.h"

#include "core.h"

#include "engine.h"
#include "game.h"
#include "profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::Core() 
:   threads_(
		kaynine::Thread<Sync>::create(g_engine.systemLoop),
		kaynine::PulseThread<Sync>::create(g_engine.resources.get()),
		kaynine::PulseThread<Sync>::create(g_engine.server.get()),
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
