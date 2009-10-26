#include "stdafx.h"

#include "logic.h"
#include "logic_component.h"

#include "core/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::update(const unsigned msec) {
    Profiler::StopWatch stopWatch(Profiler::SERVER_LOGIC);

	Sync::LogicToVideo::Writable toVideo(Sync::inst().logicToVideo());

	for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
		if (LogicComponentRegistry::inst().valid(i))
			LogicComponentRegistry::inst().get(i).update(toVideo.data().entities[i], msec);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
