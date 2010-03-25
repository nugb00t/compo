#include "stdafx.h"

#include "game.h"

#include "playground_local_client.h"
#include "playground_arbiter.h"
#include "playground_video.h"
#include "playground_factories.h"

using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PlaygroundGame : public engine::Game {
public:
	PlaygroundGame() : engine::Game(new GameLocalClient, new GameArbiter, new GameVideo, new GameEntityFactory, new GameScreenFactory) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
