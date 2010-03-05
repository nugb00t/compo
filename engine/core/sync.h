#pragma once

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Sync {
	// shared buffers
    typedef kaynine::FrameBuffer<ServerRequests::Client> ClientToArbiter;
    typedef kaynine::FrameBuffer<ServerState> ArbiterToClient;
    typedef kaynine::FrameBuffer<ServerState> ClientToVideo;

    ArbiterToClient arbiterToClient;
    ClientToArbiter clientToArbiter;
    ClientToVideo clientToVideo;

	// events
	static kaynine::Event start;
	//static kaynine::Event stop;
	static kaynine::Event exit;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
