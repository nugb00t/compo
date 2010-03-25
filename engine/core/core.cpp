#include "stdafx.h"

#include "core.h"

#include "engine.h"
#include "game.h"
#include "profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::Core() : threads_(&handles_[0], sizeof(handles_) / sizeof(HANDLE)) {
	// singletons
	Sync::inst();
	kaynine::Trace::inst();

	// threads
	handles_[0] = kaynine::Thread<Sync>::create(g_engine.resources.get());

	handles_[1] = kaynine::PulseThread<Sync>::create(g_engine.server.get());
	handles_[2] = kaynine::PulseThread<Sync>::create(g_game.video.get());

	handles_[3] = kaynine::Thread<Sync>::create(g_engine.systemLoop);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Core::run() {
	threads_.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
