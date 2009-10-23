#include "stdafx.h"

#include "logic_system.h"
#include "logic_component.h"

#include "core/profiler.h"
#include "core/sync.h"
#include "core/time.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::operator()() {
	kaynine::WaitableTimer timer(unsigned(1000.f / FRAMERATE));
	kaynine::Event signal(EXIT_SIGNAL_NAME);
	kaynine::MultipleObjects objects(timer, signal);

	for (unsigned wait = WAIT_OBJECT_0; wait == WAIT_OBJECT_0; wait = objects.waitAny()) {
		assert(wait != WAIT_FAILED);
		Profiler::StopWatch stopWatch(Profiler::LOGIC_THREAD);
		update(0);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::update(const unsigned msec) {
	Sync::LogicToVideo::Writable toVideo(Sync::inst().logicToVideo());

	for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
		if (LogicComponentRegistry::inst().valid(i))
			LogicComponentRegistry::inst().get(i).update(toVideo.data().entities[i], msec);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
