#include "stdafx.h"

#include "game.h"

#include "client/playground_local_client.h"

#include "arbiter/playground_arbiter.h"
#include "entities/playground_entity_factory.h"

using namespace game_playground;

engine::Game g_game(new GameLocalClient, new GameArbiter, new GameEntityFactory);
