#include "stdafx.h"

#include "local_client_interface.h"

#include "input/input_interface.h"

#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LocalClientInterface::LocalClientInterface() {
	LocalClient::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LocalClientInterface::update(const unsigned /*msec*/) {
	Sync::ClientToArbiter::Writable toArbiter(Sync::inst().clientToArbiter());
	if (toArbiter)
		handleControls(Input::inst().controls(), toArbiter.data());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
