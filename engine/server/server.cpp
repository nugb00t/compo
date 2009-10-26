#include "stdafx.h"

#include "server.h"

#include "arbiter.h"
#include "logic/logic.h"

#include "core/profiler.h"
#include "core/sync.h"
#include "core/time.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::operator()() {
	kaynine::WaitableTimer timer(unsigned(1000.f / FRAMERATE));
	kaynine::Event signal(EXIT_SIGNAL_NAME);
	kaynine::MultipleObjects objects(timer, signal);

	unsigned wait;
	for (wait = WAIT_OBJECT_0; wait == WAIT_OBJECT_0; wait = objects.waitAny()) {
        Profiler::StopWatch stopWatch(Profiler::SERVER);

        Arbiter::inst().update(0);
        Logic::inst().update(0);
	}
	assert(wait != WAIT_FAILED);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
