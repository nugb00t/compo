#ifndef SYNC_INCLUDED
#define SYNC_INCLUDED

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TCHAR EXIT_SIGNAL_NAME[] = _T("COMPONENTS_EXIT_SIGNAL");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sync : public kaynine::Singleton<Sync> {
public:
    typedef kaynine::FrameBuffer<ServerRequests::Client> ClientToArbiter;
    typedef kaynine::FrameBuffer<ServerState> ArbiterToClient;
    typedef kaynine::FrameBuffer<ServerState> ClientToVideo;

public:
    ClientToArbiter& clientToArbiter() { return clientToArbiterFB_; }
    ArbiterToClient& arbiterToClient() { return arbiterToClientFB_; }
    ClientToVideo& clientToVideo() { return clientToVideoFB_; }

private:
    ArbiterToClient arbiterToClientFB_;
    ClientToArbiter clientToArbiterFB_;
    ClientToVideo clientToVideoFB_;

	friend struct kaynine::Singleton<Sync>;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
