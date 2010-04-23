#include "stdafx.h"

#include "video_thread.h"

#include "engine.h"
#include "game.h"
#include "utility/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoThread::initialize() {
	kaynine::MultipleObjects events(Sync::inst().exit, Sync::inst().windowReady);

	const DWORD wait = events.waitAny();
	assert(wait != WAIT_FAILED && wait != WAIT_ABANDONED);

	if (wait == WAIT_OBJECT_0)
		return false;
	Sync::inst().windowReady.reset();

	const bool ok = video_.initialize() && gameVideo_.initialize(video_, videoFactory_, screenVideoFactory_);
	if (ok)
		TRACE_GOOD(_T("video thread started"));
	else
		TRACE_ERROR(_T("video thread failed to start"));

	return ok;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoThread::update() {
	Profiler::StopWatch stopWatch(Profiler::VIDEO);

	video_.begin();
	gameVideo_.update(video_);
	video_.end();

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoThread::terminate() {
	//gameVideo_.terminate();
	video_.terminate();
	Sync::inst().windowReady.set();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
