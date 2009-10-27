#include "stdafx.h"

#include "arbiter.h"

#include "core/profiler.h"
#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Arbiter::update(const unsigned /*msec*/) {
    Profiler::StopWatch stopWatch(Profiler::SERVER_ARBITER);

	Sync::LogicToVideo::Readable fromLogic(Sync::inst().logicToVideo());
	if (fromLogic) {
		// read client movement requests
		fromLogic.data();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
