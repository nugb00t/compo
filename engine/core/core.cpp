#include "stdafx.h"

#ifdef PLATFORM_WIN51
	#include "system/win51/message_sink_w51.h"
#endif

#include "engine.h"

#include "server/server.h"

#include "profiler.h"
#include "core.h"

using namespace engine;

namespace {
    const TCHAR* EXIT_SIGNAL_NAME = _T("COMPONENTS_EXIT_SIGNAL");

    // in milliseconds
    const unsigned CLIENT_PERIOD = 16;
    const unsigned SERVER_PERIOD = 16;
    const unsigned VIDEO_PERIOD  = 16;

    // in 100 nanoseconds
    const unsigned SERVER_DELAY  = 4 * 10;
    const unsigned VIDEO_DELAY   = 4 * 10;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::Core() 
:   quit_(EXIT_SIGNAL_NAME), 
    threads_(
		kaynine::Thread::create(
#ifdef PLATFORM_WIN51
			new MessageSinkW51,
#endif
		quit_),
		kaynine::PulseThread::create(new Server, quit_, SERVER_PERIOD, SERVER_DELAY),
		kaynine::PulseThread::create(g_engine.video, quit_, VIDEO_PERIOD,  VIDEO_DELAY)
        ) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::~Core() {
    threads_.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
