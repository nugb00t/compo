#include "stdafx.h"

#include "logic_system.h"
#include "logic_component.h"

#include "core/sync.h"
#include "core/time.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Logic::operator()() {
	kaynine::Event exitSignal(EXIT_SIGNAL_NAME);
	kaynine::Timer timer(unsigned(1000.f / FRAMERATE));

	unsigned long last = Time::inst().msec();

	while (!exitSignal.isSet()) {
		const float dt = static_cast<float>(Time::inst().msec() - last) / 1000.f;
		last = Time::inst().msec();

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

