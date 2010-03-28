#pragma once

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Sync : public kaynine::Singleton<Sync> {
	// shared buffers
    typedef kaynine::FrameBuffer<ServerRequests::Client> ClientToArbiter;
    typedef kaynine::FrameBuffer<ServerState> ArbiterToClient;
    typedef kaynine::FrameBuffer<ServerState> ClientToVideo;

    ArbiterToClient arbiterToClient;
    ClientToArbiter clientToArbiter;
    ClientToVideo clientToVideo;

	// events
	//kaynine::Event start;
	//kaynine::Event stop;
	kaynine::Event exit;
	kaynine::Event windowReady;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
