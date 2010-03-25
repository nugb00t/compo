#pragma once

#include "server/server_data.h"

#include "game_arbiter.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameArbiter : public engine::Arbiter {
public:
	virtual ~GameArbiter() {}

protected:
    // interface: ArbiterInterface
    virtual void marshall(const engine::ServerState& last, const engine::ServerRequests& requests, engine::ServerState& next);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
