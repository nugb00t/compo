#pragma once

#include "server/server_data.h"

#include "game_flow.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameFlow : public engine::GameFlow {
public:
    // interface: GameFlow
	virtual void initialize(engine::ServerState& first);
	virtual void advance(const engine::ServerState& last, engine::ServerState& next);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}