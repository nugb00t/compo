#ifndef PLAYGROUND_GAME_INCLUDED
#define PLAYGROUND_GAME_INCLUDED

#include "arbiter/playground_arbiter.h"
#include "client/playground_client.h"
#include "entities/orb/orb.h"
//#include "screens/profiler/profiler_screen.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Game {
private:
    // game subsystems
    GameArbiter arbiter_;
	GameClient client_;
	Orb orb_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
