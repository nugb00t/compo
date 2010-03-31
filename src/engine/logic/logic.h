#pragma once

#include "server/server_data.h"

#include "game_factories.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Logic {
public:
	Logic(LogicFactory* const logicFactory) : logicFactory_(logicFactory) {}

	void initialize();
	void decide(const ServerState& last, ServerRequests::Entity entities[ServerState::MAX_ENTITIES]);

private:
	boost::scoped_ptr<LogicComponent> entities_[ServerState::MAX_ENTITIES];

	LogicFactory* const logicFactory_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
