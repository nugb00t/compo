#pragma once

#include "input/input.h"
#include "game_local_client.h"

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalClient {
public:
	LocalClient(GameLocalClient* const gameLocalClient) : gameLocalClient_(gameLocalClient) {}
	void update();

private:
	const boost::scoped_ptr<GameLocalClient> gameLocalClient_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
