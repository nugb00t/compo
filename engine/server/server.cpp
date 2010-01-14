#include "stdafx.h"

#include "server.h"

#include "arbiter/arbiter_interface.h"
#include "logic/logic.h"

#include "core/profiler.h"
#include "core/sync.h"
#include "core/time.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Server::initialize(Params* params) {
    assert(params && params->registry);
    Logic::inst().initialize(params->registry);

    states_.advance(States::CLEAR_FRAME);

	states_.get().entities[0].rotation.identity();
	states_.get().entities[0].rotationalVelocity.identity();
	states_.get().entities[0].active = true;

	states_.get().clients[0].rotation.identity();
	states_.get().clients[0].rotationalVelocity.identity();
	states_.get().clients[0].active = true;

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Server::update() {
    Profiler::StopWatch stopWatch(Profiler::SERVER);

    states_.advance(States::CLEAR_FRAME);

    ServerRequests requests;
    memset(&requests, 0, sizeof(requests));

    Logic::inst().decide(states_.get(-1), requests.entities);

    Sync::ClientToArbiter::Readable fromClient(Sync::inst().clientToArbiter());
    if (fromClient)
        requests.clients[0] = fromClient.data();

    Arbiter::inst().marshall(states_.get(-1), requests, states_.get());

    Sync::ArbiterToClient::Writable toClient(Sync::inst().arbiterToClient());
    if (toClient)
        toClient.data() = states_.get();

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
