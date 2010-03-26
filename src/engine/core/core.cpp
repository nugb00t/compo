#include "stdafx.h"

#include "core.h"

#include "engine.h"
#include "video/video_thread.h"

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
	VideoThread video;

	HANDLE handles[] = {
		kaynine::Thread<Sync>::create(Engine::inst().resources.get()),
		kaynine::PulseThread<Sync>::create(Engine::inst().server.get()),
		kaynine::PulseThread<Sync>::create(&video),
		kaynine::Thread<Sync>::create(Engine::inst().systemLoop),
	};

	kaynine::Handles threads(&handles[0], sizeof(handles) / sizeof(HANDLE));
	threads.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
