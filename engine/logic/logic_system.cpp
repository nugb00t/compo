#include "stdafx.h"

#include "logic_system.h"
#include "logic_component.h"

#include "core/core.h"
#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::operator()() {
	kaynine::Event exitSignal(EXIT_SIGNAL_NAME);
	kaynine::WaitableTimer timer(unsigned(1000.f / FRAMERATE));

	time_t last = Core::inst().time();
	float dt;

	while (!exitSignal.isSet()) {
		dt = static_cast<float>(Core::inst().time() - last);
		last = Core::inst().time();

		Logic::inst().update(dt);

		timer.wait(unsigned(1000.f / FRAMERATE * 2));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::update(const float dt) {
	Sync::LogicToVideoWritable toVideo(Sync::inst().logicToVideo());

	for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
		if (LogicComponentRegistry::inst().valid(i))
			LogicComponentRegistry::inst().get(i).update(toVideo->entityParams[i], dt);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

