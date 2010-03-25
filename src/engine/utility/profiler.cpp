#include "stdafx.h"

#include "profiler.h"

#include "engine.h"

using namespace engine;

const uint Profiler::SECTION_COLORS[SECTION_COUNT] = {
	0x08ffffff,		// SYSTEM
	0x08ff0000,		// SERVER
	0x08ffff00,		// SERVER_ARBITER
	0x08ff00ff,		// SERVER_LOGIC
	0x0800ffff,		// LOCAL_CLIENT
	0x0800ff00 		// VIDEO
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Profiler::StopWatch::StopWatch(const Section section)
: section_(section), start_(g_engine.time->msec()) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Profiler::StopWatch::~StopWatch() {
	g_engine.profiler->track(section_, start_, g_engine.time->msec());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Profiler::Profiler() {
	// avoid uninitialized section counters by placing dummy periods in the beginning
	for (uint section = 0; section < SECTION_COUNT; ++section)
		track((Section)section, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Profiler::Period& Profiler::get(const Section section, const int age) const {
	assert(section < SECTION_COUNT);
	kaynine::AutoLock<> lock(guard_);
	return trackers_[section].get(age);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Profiler::track(const Section section, const uint begin, const uint end) {
	assert(section < SECTION_COUNT);

	kaynine::AutoLock<> lock(guard_);
	trackers_[section].advance();
	trackers_[section].get() = Period(begin, end);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
