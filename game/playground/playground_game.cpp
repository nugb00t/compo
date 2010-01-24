#include "stdafx.h"

#include "game.h"

#include "client/playground_local_client.h"
#include "arbiter/playground_arbiter.h"
#include "playground_factories.h"

using namespace game_playground;

engine::Game g_game(new GameLocalClient, new GameArbiter, new GameEntityFactory, new GameScreenFactory);
