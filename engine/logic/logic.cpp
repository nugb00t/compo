#include "stdafx.h"

#include "logic.h"
#include "logic_component.h"

#include "core/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::decide(const ServerState& last, ServerRequests& requests) {
    Profiler::StopWatch stopWatch(Profiler::SERVER_LOGIC);

	for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
		if (LogicComponentRegistry::inst().valid(i))
			LogicComponentRegistry::inst().get(i).decide(last, requests.entities[i]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
