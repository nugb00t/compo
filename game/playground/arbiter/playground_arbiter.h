#ifndef PLAYGROUND_ARBITER_INCLUDED
#define PLAYGROUND_ARBITER_INCLUDED

#include "arbiter/arbiter.h"
#include "server/server_data.h"

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

#endif
