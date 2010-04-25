#include "stdafx.h"

#include "video_thread.h"

#include "engine.h"
#include "game.h"
#include "utility/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoThread::initialize() {
#ifdef VIDEO_DIRECT3D9
	video_.reset(new VideoD3D9);
#endif

	const bool ok = video_->initialize() && gameVideo_.initialize(*video_, videoFactory_, screenVideoFactory_);
	if (ok)
		TRACE_GOOD(_T("video thread started"));
	else
		TRACE_ERROR(_T("video thread failed to start"));

	return ok;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoThread::update() {
	Profiler::StopWatch stopWatch(Profiler::VIDEO);

	video_->begin();
	const bool ok = gameVideo_.update(*video_);
	video_->end();

	return ok;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoThread::terminate() {
	//gameVideo_.terminate();
	video_->terminate();
	video_.reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
