#include "stdafx.h"

#include "core.h"

#include "engine.h"
#include "game.h"

#include "utility/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::Core() {
	Sync::inst();
	kaynine::Trace::inst();

	Engine::inst();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Core::run() {
	HANDLE handles[] = {
		kaynine::Thread<Sync>::create(Engine::inst().resources.get()),
		kaynine::PulseThread<Sync>::create(Engine::inst().server.get()),
		kaynine::PulseThread<Sync>::create(Game::inst().video.get()),
		kaynine::Thread<Sync>::create(Engine::inst().systemLoop),
	};

	kaynine::Handles threads(&handles[0], sizeof(handles) / sizeof(HANDLE));
	threads.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
