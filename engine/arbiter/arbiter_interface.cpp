#include "stdafx.h"

#include "arbiter_interface.h"

#include "core/profiler.h"
#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ArbiterInterface::update(const unsigned /*msec*/) {
    Profiler::StopWatch stopWatch(Profiler::SERVER_ARBITER);

    Sync::ClientToArbiter::Readable fromClient(Sync::inst().clientToArbiter());
	if (fromClient)
        marshall(fromClient.data());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
