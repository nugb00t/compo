#include "stdafx.h"

#include "video_thread.h"

#include "engine.h"
#include "game.h"
#include "utility/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoThread::initialize() {
	HANDLE handles[] = { Sync::inst().exit.handle(), Sync::inst().windowReady.handle() };
	kaynine::Handles events(&handles[0], sizeof(handles) / sizeof(HANDLE));

	const DWORD wait = events.waitAny();
	assert(wait != WAIT_FAILED && wait != WAIT_ABANDONED);

	if (wait == WAIT_OBJECT_0)
		return false;
	Sync::inst().windowReady.reset();

	return video_->initialize() && gameVideo_->initialize(video_.get(), videoFactory_.get(), screenVideoFactory_.get());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoThread::update() {
	Profiler::StopWatch stopWatch(Profiler::VIDEO);

	video_->clear();

	if (video_->begin()) {
		gameVideo_->update(video_.get());
		video_->end();
	}
	
	video_->present();

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
