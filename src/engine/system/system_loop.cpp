#include "stdafx.h"

#include "system_loop.h"

#include "engine.h"
#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SystemLoop::terminate() {
	Sync::inst().windowReady.wait(10 * 1000);
	Engine::inst().window->destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
