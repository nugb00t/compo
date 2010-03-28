#include "stdafx.h"

#include "playground_arbiter.h"
#include "playground_local_client.h"
#include "playground_video.h"
#include "playground_factories.h"

using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PlaygroundGame::PlaygroundGame() 
: engine::Game(new GameLocalClient,
			   new GameArbiter,
			   new GameVideo,
			   new LogicFactory,
			   new VideoFactory,
			   new ScreenVideoFactory) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
