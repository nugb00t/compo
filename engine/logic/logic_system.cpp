#include "stdafx.h"

#include "logic_system.h"

#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::operator()() {
	kaynine::Event exitSignal(Sync::EXIT_SIGNAL_NAME);
	while (!exitSignal.isSet()) {
		//update(0);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

