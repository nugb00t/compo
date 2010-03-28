#pragma once

#include "game_arbiter.h"
#include "game_local_client.h"
#include "game_video.h"
#include "game_factories.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Game {
public:
	GameArbiter* const arbiter;
	GameLocalClient* const localClient;
	GameVideo* const video;

	LogicFactory* const logicFactory;
	VideoFactory* const videoFactory;
	ScreenVideoFactory* const screenVideoFactory;

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
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
