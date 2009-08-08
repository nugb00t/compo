#include "stdafx.h"

#include "logic_system.h"

#include "core/core.h"
#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::operator()() {
	kaynine::Event exitSignal(sync::EXIT_SIGNAL_NAME);
	while (!exitSignal.isSet()) {
		//update(0);
	}

	kaynine::WaitableTimer timer(sync::LOGIC_FRAMETIME);

	time_t last = Core::inst().time();
	float dt;

	while (!exitSignal.isSet()) {
		dt = static_cast<float>(Core::inst().time() - last);
		last = Core::inst().time();

		Logic::inst().update(dt);

		timer.wait(sync::VIDEO_FRAMETIME * 2);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Logic::update(const float /*dt*/) {
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

