#include "stdafx.h"

#include "core.h"

#include "engine.h"
#include "filesystem/filesystem_thread.h"
#include "server/server_thread.h"
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
	FileSystemThread fileSystem;
	ServerThread server;
	VideoThread video;

	HANDLE handles[] = {
		kaynine::Thread<Sync>::create(&fileSystem),
		kaynine::PulseThread<Sync>::create(&server),
		kaynine::PulseThread<Sync>::create(&video),
		kaynine::Thread<Sync>::create(Engine::inst().systemLoop),
	};

	kaynine::Handles threads(&handles[0], sizeof(handles) / sizeof(HANDLE));
	threads.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
