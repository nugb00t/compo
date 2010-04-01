#pragma once

#include "input/input.h"

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameLocalClient {
public:
	virtual ~GameLocalClient() {}
	virtual void handleControls(const Controls& controls, ServerRequests::Client& request) = 0;
	virtual void showWorld(const ServerState& fromArbiter, ServerState& toVideo) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
