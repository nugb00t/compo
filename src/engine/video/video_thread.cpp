#include "stdafx.h"

#include "video_thread.h"

#include "engine.h"
#include "game.h"
#include "utility/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoThread::initialize() {
#ifdef VIDEO_DIRECT3D9
	video_.reset(new VideoD3D9(window_));
#endif

	if (video_->initialize()) {
		gameVideo_.reset(game_.createVideo());
		if (gameVideo_->initialize(*video_)) {
			TRACE_GOOD(_T("video thread started"));
			return true;
		}
	}
	
	TRACE_ERROR(_T("video thread failed to start"));
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoThread::update() {
	Profiler::StopWatch stopWatch(Profiler::VIDEO);

	video_->begin();
	const bool ok = gameVideo_->update(*video_);
	video_->end();

	return ok;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoThread::terminate() {
	gameVideo_->terminate();
	gameVideo_.reset();
	
	video_->terminate();
	video_.reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
