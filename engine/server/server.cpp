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

	states_.advance(States::CLEAR_FRAME);
	spawn();

	unsigned wait;
	ServerRequests requests;
	for (wait = WAIT_OBJECT_0; wait == WAIT_OBJECT_0; wait = objects.waitAny()) {
        Profiler::StopWatch stopWatch(Profiler::SERVER);

		states_.advance(States::CLEAR_FRAME);
		memset(&requests, 0, sizeof(requests));

		Logic::inst().decide(states_.get(-1), requests);

		Sync::ClientToArbiter::Readable fromClient(Sync::inst().clientToArbiter());
		if (fromClient)
			requests.clients[0] = fromClient.data();

		Arbiter::inst().marshall(states_.get(-1), requests, states_.get());

		Sync::ArbiterToClient::Writable toClient(Sync::inst().arbiterToClient());
		if (toClient)
			toClient.data() = states_.get();
	}
	assert(wait != WAIT_FAILED);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Server::spawn() {
	states_.get().entities[0].rotation.identity();
	states_.get().entities[0].rotationalVelocity.identity();
	states_.get().entities[0].active = true;

	states_.get().clients[0].rotation.identity();
	states_.get().clients[0].rotationalVelocity.identity();
	states_.get().clients[0].active = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
