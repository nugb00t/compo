#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "client/local_client.h"

#include "arbiter/arbiter.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Game {
	const boost::scoped_ptr<LocalClient> localClient;
	const boost::scoped_ptr<Arbiter> arbiter;

	Game(LocalClient* localClient_, Arbiter* arbiter_) : localClient(localClient_), arbiter(arbiter_) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern Game g_game;

}

#endif
