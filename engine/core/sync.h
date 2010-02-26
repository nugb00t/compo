#pragma once

#include "server/server_data.h"

namespace {
	const TCHAR* QUIT_SIGNAL_NAME = _T("COMPONENTS_EXIT_SIGNAL");
}

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Sync {
    typedef kaynine::FrameBuffer<ServerRequests::Client> ClientToArbiter;
    typedef kaynine::FrameBuffer<ServerState> ArbiterToClient;
    typedef kaynine::FrameBuffer<ServerState> ClientToVideo;

    ArbiterToClient arbiterToClient;
    ClientToArbiter clientToArbiter;
    ClientToVideo clientToVideo;

	kaynine::Event quit;

	Sync() : quit(QUIT_SIGNAL_NAME) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
