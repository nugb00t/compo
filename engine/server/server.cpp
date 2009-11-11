#include "stdafx.h"

#include "server.h"

#include "arbiter/arbiter_interface.h"
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

        // TODO: gather logic requests

        // TODO: gather client requests

        // TODO: let arbiter sort 'em out

        // TODO: send updated views to the clients

        Logic::inst().update(0);


        Sync::ClientToArbiter::Readable fromClient(Sync::inst().clientToArbiter());
        if (fromClient)
            Arbiter::inst().marshall(fromClient.data());
	}
	assert(wait != WAIT_FAILED);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
