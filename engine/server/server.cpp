#include "stdafx.h"

#include "server.h"

#include "engine.h"
#include "game.h"

#include "core/profiler.h"
#include "core/sync.h"
#include "core/time.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

kaynine::Event& Server::quit() { 
	return g_engine.sync->quit; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Server::initialize() {
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

    g_engine.logic->decide(states_.get(-1), requests.entities);

    Sync::ClientToArbiter::Readable fromClient(g_engine.sync->clientToArbiter);
	if (fromClient && fromClient.age())
		::OutputDebugString(_T("Server::update(): failed to open Arbiter package\n"));

    if (fromClient)
        requests.clients[0] = fromClient.data();

    g_game.arbiter->marshall(states_.get(-1), requests, states_.get());

    Sync::ArbiterToClient::Writable toClient(g_engine.sync->arbiterToClient);
    assert(toClient);
	
	toClient.data() = states_.get();

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
