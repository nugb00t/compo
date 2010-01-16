#ifndef GAME_HUB_INCLUDED
#define GAME_HUB_INCLUDED

#include "entity_factory.h"

#include "client/local_client.h"

#include "arbiter/arbiter.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Game {
	const boost::scoped_ptr<LocalClient> localClient;
	const boost::scoped_ptr<Arbiter> arbiter;
	const boost::scoped_ptr<EntityFactory> entityFactory;

	Game(LocalClient* localClient_, Arbiter* arbiter_, EntityFactory* entityFactory_) 
		: localClient(localClient_), arbiter(arbiter_), entityFactory(entityFactory_) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
