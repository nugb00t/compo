#include "stdafx.h"

#include "local_client_interface.h"

#include "input/input_interface.h"

#include "core/profiler.h"
#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LocalClientInterface::update(const unsigned /*msec*/) {
    Profiler::StopWatch stopWatch(Profiler::LOCAL_CLIENT);

	Sync::ClientToArbiter::Writable toArbiter(Sync::inst().clientToArbiter());
	if (toArbiter)
		handleControls(Input::inst().controls(), toArbiter.data());

	Sync::ArbiterToClient::Readable fromArbiter(Sync::inst().arbiterToClient());
	Sync::ClientToVideo::Writable toVideo(Sync::inst().clientToVideo());
	if (fromArbiter && toVideo)
		showWorld(fromArbiter.data(), toVideo.data());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
