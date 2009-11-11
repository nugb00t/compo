#ifndef PLAYGROUND_ARBITER_INCLUDED
#define PLAYGROUND_ARBITER_INCLUDED

#include "arbiter/arbiter_interface.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameArbiter : engine::ArbiterInterface {
private:
    // interface: ArbiterInterface
    virtual void marshall(const ServerView& last, const ClientRequest& requests, ServerView& next);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
