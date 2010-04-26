#pragma once

#include "server/server_data.h"

#include "game.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Logic {
public:
	Logic(GameFactory& game) : game_(game) {}

	void initialize();
	void decide(const ServerState& last, ServerRequests::Entity entities[ServerState::MAX_ENTITIES]);

private:
	GameFactory& game_;
	
	boost::scoped_ptr<LogicComponent> entities_[ServerState::MAX_ENTITIES];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
