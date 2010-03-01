#include "stdafx.h"

#include "logic.h"
#include "logic_component.h"

#include "game.h"

#include "core/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Logic::Logic() {
	memset(&entities_, 0, sizeof(entities_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::decide(const ServerState& last, ServerRequests::Entity entities[ServerState::MAX_ENTITIES]) {
    Profiler::StopWatch stopWatch(Profiler::SERVER_LOGIC);

	// TEMP
	if (!entities_[0])
		entities_[0] = g_game.entityFactory->createLogicComponent(0);
	// TEMP

	for (uint i = 0; i < ServerState::MAX_ENTITIES; ++i)
		if (entities_[i])
			entities_[i]->decide(last, entities[i]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
