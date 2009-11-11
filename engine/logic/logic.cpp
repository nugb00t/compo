#include "stdafx.h"

#include "logic.h"
#include "logic_component.h"

#include "core/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::decide(const ServerView& last, ClientRequest& requests) {
    Profiler::StopWatch stopWatch(Profiler::SERVER_LOGIC);

	Sync::ClientToVideo::Writable toVideo(Sync::inst().clientToVideo());

	for (unsigned i = 0; i < ServerView::MAX_ENTITIES; ++i)
		if (LogicComponentRegistry::inst().valid(i))
			LogicComponentRegistry::inst().get(i).update(toVideo.data().entities[i], msec);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
