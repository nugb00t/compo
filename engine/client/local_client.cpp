#include "stdafx.h"

#include "local_client.h"

#include "core/profiler.h"
#include "core/sync.h"

#ifdef PLATFORM_WIN51
#include "input/win51/input_w51.h"
#endif

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LocalClient::LocalClient() 
: input_(
#ifdef PLATFORM_WIN51
         new InputW51
#endif
         ) {};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LocalClient::update() {
    Profiler::StopWatch stopWatch(Profiler::LOCAL_CLIENT);

	Sync::ClientToArbiter::Writable toArbiter(Sync::inst().clientToArbiter());
	if (toArbiter) {
		memset(&toArbiter.data(), 0, sizeof(toArbiter.data()));
		handleControls(input_->controls(), toArbiter.data());
	}

	Sync::ArbiterToClient::Readable fromArbiter(Sync::inst().arbiterToClient());
	Sync::ClientToVideo::Writable toVideo(Sync::inst().clientToVideo());
	if (fromArbiter && toVideo)
		showWorld(fromArbiter.data(), toVideo.data());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
