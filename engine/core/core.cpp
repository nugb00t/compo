#include "stdafx.h"

#include "core.h"
#include "profiler.h"

#ifdef PLATFORM_WIN51
	#include "system/win51/message_sink_w51.h"
#endif

#ifdef VIDEO_DIRECT3D9
	#include "video/direct3d9/video_d3d9.h"
#endif

#include "server/server.h"

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
:   signal_(EXIT_SIGNAL_NAME), 
    threads_(
#ifdef PLATFORM_WIN51
        kaynine::thread<MessageSinkW51>(MessageSinkW51::Params(signal_, CLIENT_PERIOD)),
#endif
        kaynine::PulseThread<Server>::create(signal_, SERVER_PERIOD, SERVER_DELAY),
#ifdef VIDEO_DIRECT3D9
        kaynine::PulseThread<VideoD3D9>::create(signal_, VIDEO_PERIOD,  VIDEO_DELAY)
#endif
        ) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::~Core() {
    threads_.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
