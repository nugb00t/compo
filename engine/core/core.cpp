#include "stdafx.h"

#ifdef PLATFORM_WIN51
	#include "system/win51/message_sink_w51.h"
#endif

#ifdef VIDEO_DIRECT3D9
	#include "video/direct3d9/video_d3d9.h"
#endif

#include "server/server.h"
#include "logic/logic_component.h"

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
#ifdef PLATFORM_WIN51
    kaynine::Thread<MessageSinkW51>::create(MessageSinkW51::Params(CLIENT_PERIOD), quit_),
#endif
    kaynine::PulseThread<Server>::create(Server::Params(&LogicComponentRegistry::inst()), quit_, SERVER_PERIOD, SERVER_DELAY),
#ifdef VIDEO_DIRECT3D9
    kaynine::PulseThread<VideoD3D9>::create(VideoD3D9::Params(&VideoComponentRegistry::inst()), quit_, VIDEO_PERIOD,  VIDEO_DELAY)
#endif
        ) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Core::~Core() {
    threads_.waitAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
