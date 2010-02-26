#pragma once

#include "client/local_client.h"
#include "server/server_data.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameLocalClient : public engine::LocalClient {
public:
	virtual ~GameLocalClient() {}

public:
    // interface: LocalClientInterface
	virtual void handleControls(const engine::InputData& controls, engine::ServerRequests::Client& request);
	virtual void showWorld(const engine::ServerState& fromArbiter, engine::ServerState& toVideo);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
