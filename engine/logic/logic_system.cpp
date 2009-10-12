#include "stdafx.h"

#include "logic_system.h"
#include "logic_component.h"

#include "utility/timer.h"
#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::operator()() {
	kaynine::Event exitSignal(EXIT_SIGNAL_NAME);
	kaynine::WaitableTimer timer(unsigned(1000.f / FRAMERATE));

	unsigned long last = Timer::inst().msec();

	while (!exitSignal.isSet()) {
		const float dt = static_cast<float>(Timer::inst().msec() - last) / 1000.f;
		last = Timer::inst().msec();

		Logic::inst().update(dt);

		timer.wait(unsigned(1000.f / FRAMERATE * 2));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::update(const float dt) {
	Sync::LogicToVideoWritable toVideo(Sync::inst().logicToVideo());

	for (unsigned i = 0; i < Sync::MAX_ENTITIES; ++i)
		if (LogicComponentRegistry::inst().valid(i))
			LogicComponentRegistry::inst().get(i).update(toVideo->entities[i], dt);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

