#include "stdafx.h"

#include "local_client_interface.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LocalClientInterface::LocalClientInterface() {
	LocalClient::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LocalClientInterface::update() {
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////