#pragma once

#include "game_factories.h"
#include "game_arbiter.h"
#include "client/local_client.h"
#include "video/video.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Game {
	const boost::scoped_ptr<LocalClient> localClient;
	const boost::scoped_ptr<Arbiter> arbiter;
	const boost::scoped_ptr<Video> video;

	const boost::scoped_ptr<EntityFactory> entityFactory;
	const boost::scoped_ptr<ScreenFactory> screenFactory;

	Game(LocalClient* localClient_, Arbiter* arbiter_, Video* video_, EntityFactory* entityFactory_, ScreenFactory* screenFactory_) 
		: localClient(localClient_), arbiter(arbiter_), video(video_), entityFactory(entityFactory_), screenFactory(screenFactory_) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
