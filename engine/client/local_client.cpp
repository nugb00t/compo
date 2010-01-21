#include "stdafx.h"

#include "local_client.h"

#include "engine.h"

#include "core/profiler.h"
#include "core/sync.h"

#ifdef PLATFORM_WIN51
#include "input/win51/input_w51.h"
#endif

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LocalClient::update() {
    Profiler::StopWatch stopWatch(Profiler::LOCAL_CLIENT);

	Sync::ClientToArbiter::Writable toArbiter(g_engine.sync->clientToArbiter);
	assert(toArbiter);

	memset(&toArbiter.data(), 0, sizeof(toArbiter.data()));
	handleControls(g_engine.input->controls(), toArbiter.data());

	Sync::ArbiterToClient::Readable fromArbiter(g_engine.sync->arbiterToClient);
	Sync::ClientToVideo::Writable toVideo(g_engine.sync->clientToVideo);
	assert(toVideo);

	if (fromArbiter)
		showWorld(fromArbiter.data(), toVideo.data());
	DEBUG_ONLY(else ::OutputDebugString(_T("LocalClient::update(): failed to open Arbiter package\n")));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
