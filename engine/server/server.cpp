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

		states_.advance(States::CLEAR_FRAME);
		requests_.advance(Requests::CLEAR_FRAME);

		Logic::inst().decide(states_.get(-1), requests_.get());

		Sync::ClientToArbiter::Readable fromClient(Sync::inst().clientToArbiter());
		if (fromClient)
			requests_.get().clients[0] = fromClient.data();

		Arbiter::inst().marshall(states_.get(-1), requests_.get(), states_.get());

		Sync::ArbiterToClient::Writable toClient(Sync::inst().arbiterToClient());
		if (toClient)
			toClient.data() = states_.get();
	}
	assert(wait != WAIT_FAILED);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
