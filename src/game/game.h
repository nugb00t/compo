#pragma once

#include "game_arbiter.h"
#include "game_local_client.h"
#include "video/video.h"
#include "game_factories.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Game : public kaynine::Holder<Game> {
	const boost::scoped_ptr<Arbiter> arbiter;
	const boost::scoped_ptr<GameLocalClient> localClient;
	const boost::scoped_ptr<Video> video;

	const boost::scoped_ptr<EntityFactory> entityFactory;
	const boost::scoped_ptr<ScreenFactory> screenFactory;

	Game(GameLocalClient* localClient_, Arbiter* arbiter_, Video* video_, EntityFactory* entityFactory_, ScreenFactory* screenFactory_) 
		: localClient(localClient_), arbiter(arbiter_), video(video_), entityFactory(entityFactory_), screenFactory(screenFactory_) { set(*this); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
