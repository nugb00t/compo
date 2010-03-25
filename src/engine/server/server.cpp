#include "stdafx.h"

#include "server.h"

#include "engine.h"
#include "game.h"

#include "core/sync.h"
#include "core/time.h"
#include "utility/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Server::initialize() {
    states_.advance(States::CLEAR_FRAME);

	states_.get().entities[0].rotation.identity();
	states_.get().entities[0].rotationalVelocity.identity();
	states_.get().entities[0].active = true;

	states_.get().clients[0].rotation.identity();
	states_.get().clients[0].rotationalVelocity.identity();
	states_.get().clients[0].active = true;

	// TEMP
	//entities_[0]
	// TEMP

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Server::update() {
    Profiler::StopWatch stopWatch(Profiler::SERVER);

    states_.advance(States::CLEAR_FRAME);

    ServerRequests requests;
    memset(&requests, 0, sizeof(requests));

    Engine::inst().logic->decide(states_.get(-1), requests.entities);

    Sync::ClientToArbiter::Readable fromClient(Sync::inst().clientToArbiter);
	//if (fromClient && fromClient.age())
	//	::OutputDebugString(_T("Server::update(): failed to open GameArbiter package\n"));

    if (fromClient)
        requests.clients[0] = fromClient.data();

	{
		Profiler::StopWatch stopWatch(Profiler::SERVER_ARBITER);
	    Game::inst().arbiter->marshall(states_.get(-1), requests, states_.get());
	}

    Sync::ArbiterToClient::Writable toClient(Sync::inst().arbiterToClient);
    assert(toClient);
	
	toClient.data() = states_.get();

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
