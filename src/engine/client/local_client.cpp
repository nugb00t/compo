#include "stdafx.h"

#include "local_client.h"

#include "engine.h"
#include "game.h"

#include "core/sync.h"
#include "utility/profiler.h"

#ifdef PLATFORM_WIN51
#include "input/win51/input_w51.h"
#endif

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LocalClient::update() {
    Profiler::StopWatch stopWatch(Profiler::LOCAL_CLIENT);

	Sync::ClientToArbiter::Writable toArbiter(Sync::inst().clientToArbiter);
	assert(toArbiter);

	memset(&toArbiter.data(), 0, sizeof(toArbiter.data()));
	g_game.localClient->handleControls(g_engine.input->controls(), toArbiter.data());

	Sync::ArbiterToClient::Readable fromArbiter(Sync::inst().arbiterToClient);
	//if (fromArbiter && fromArbiter.age())
	//	::OutputDebugString(_T("LocalClient::update(): failed to open Arbiter package\n"));

	Sync::ClientToVideo::Writable toVideo(Sync::inst().clientToVideo);
	assert(toVideo);

	if (fromArbiter)
		g_game.localClient->showWorld(fromArbiter.data(), toVideo.data());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
