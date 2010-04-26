#include "stdafx.h"

#include "local_client_thread.h"

#include "engine.h"
#include "game.h"

#include "core/sync.h"
#include "utility/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool LocalClientThread::initialize() {
	gameLocalClient_.reset(game_.createLocalClient());
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool LocalClientThread::update() {
    Profiler::StopWatch stopWatch(Profiler::LOCAL_CLIENT);

	Sync::ClientToArbiter::Writable toArbiter(Sync::inst().clientToArbiter);
	assert(toArbiter);

	memset(&toArbiter.data(), 0, sizeof(toArbiter.data()));
	gameLocalClient_->handleControls(controls_, toArbiter.data());

	Sync::ArbiterToClient::Readable fromArbiter(Sync::inst().arbiterToClient);
	//if (fromArbiter && fromArbiter.age())
	//	::OutputDebugString(_T("LocalClient::update(): failed to open GameArbiter package\n"));

	Sync::ClientToVideo::Writable toVideo(Sync::inst().clientToVideo);
	assert(toVideo);

	if (fromArbiter)
		gameLocalClient_->showWorld(fromArbiter.data(), toVideo.data());
		
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LocalClientThread::terminate() {
	gameLocalClient_.reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
