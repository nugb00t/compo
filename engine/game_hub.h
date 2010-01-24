#ifndef GAME_HUB_INCLUDED
#define GAME_HUB_INCLUDED

#include "factories.h"

#include "client/local_client.h"

#include "arbiter/arbiter.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Game {
	const boost::scoped_ptr<LocalClient> localClient;
	const boost::scoped_ptr<Arbiter> arbiter;

	const boost::scoped_ptr<EntityFactory> entityFactory;
	const boost::scoped_ptr<ScreenFactory> screenFactory;

	Game(LocalClient* localClient_, Arbiter* arbiter_, EntityFactory* entityFactory_, ScreenFactory* screenFactory_) 
		: localClient(localClient_), arbiter(arbiter_), entityFactory(entityFactory_), screenFactory(screenFactory_) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
