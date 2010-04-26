#pragma once

#include "server/server_data.h"

#include "game.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameLocalClient : public engine::GameLocalClient {
public:
    // interface: LocalClientInterface
	virtual void handleControls(const engine::Controls& controls, engine::ServerRequests::Client& request);
	virtual void showWorld(const engine::ServerState& fromArbiter, engine::ServerState& toVideo);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
