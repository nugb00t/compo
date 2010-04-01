#pragma once

#include "game_arbiter.h"
#include "game_local_client.h"
#include "game_video.h"
#include "game_factories.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Game {
public:
	const boost::scoped_ptr<GameArbiter> arbiter;
	const boost::scoped_ptr<GameLocalClient> localClient;
	const boost::scoped_ptr<GameVideo> video;

	const boost::scoped_ptr<LogicFactory> logicFactory;
	const boost::scoped_ptr<VideoFactory> videoFactory;
	const boost::scoped_ptr<ScreenVideoFactory> screenVideoFactory;

	Game(GameLocalClient* const localClient_, 
		 GameArbiter* const arbiter_, 
		 GameVideo* const video_, 
		 LogicFactory* const logicFactory_, 
		 VideoFactory* const videoFactory_, 
		 ScreenVideoFactory* const screenVideoFactory_) 
	: localClient(localClient_),
	  arbiter(arbiter_),
	  video(video_),
	  logicFactory(logicFactory_),
	  videoFactory(videoFactory_),
	  screenVideoFactory(screenVideoFactory_)
	{}

	virtual ~Game() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
