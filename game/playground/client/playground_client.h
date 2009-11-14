#ifndef PLAYGROUND_CLIENT_INCLUDED
#define PLAYGROUND_CLIENT_INCLUDED

#include "client/local_client_interface.h"
#include "server/server_data.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameClient : engine::LocalClientInterface {
private:
    // interface: LocalClientInterface
	virtual void handleControls(const engine::InputData& controls, engine::ServerRequests::Client& request);
	virtual void showWorld(const engine::ServerState& fromArbiter, engine::ServerState& toVideo);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
