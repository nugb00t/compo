#include "stdafx.h"

#include "logic.h"

#include "utility/profiler.h"

#include "game.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::initialize() {
	if (!entities_[0])
		entities_[0].reset(game_.createLogicComponent(0));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::decide(const ServerState& last, ServerRequests::Entity entities[ServerState::MAX_ENTITIES]) {
    Profiler::StopWatch stopWatch(Profiler::SERVER_LOGIC);

	for (uint i = 0; i < ServerState::MAX_ENTITIES; ++i)
		if (entities_[i])
			entities_[i]->decide(last, entities[i]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
