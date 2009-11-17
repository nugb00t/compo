#include "stdafx.h"

#include "video_interface.h"

#include "core/sync.h"
#include "core/profiler.h"
#include "video/video_component.h"
#include "window/window_interface.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoInterface::operator()() {
	if (Video::inst().startup()) {
		// TODO: move camera to its own entity
		camera_ = createCamera();
		assert(camera_);

		kaynine::WaitableTimer timer(unsigned(1000.f / FRAMERATE));
		kaynine::Event exitSignal(EXIT_SIGNAL_NAME);
		kaynine::MultipleObjects objects(timer, exitSignal);

		unsigned wait;
		for (wait = WAIT_OBJECT_0; wait == WAIT_OBJECT_0; wait = objects.waitAny()) {
			if (exitSignal.isSet())
				break;

			Profiler::StopWatch stopWatch(Profiler::VIDEO);
			Video::inst().update(0);
		}
		assert(wait != WAIT_FAILED);
	}

	Video::inst().shutdown();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoInterface::update(const unsigned msec) {
	clear();

	if (begin()) {
		camera_->update(msec);

		Sync::ClientToVideo::Readable fromClient(Sync::inst().clientToVideo());
		if (fromClient)
			for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
				if (EntityVideoComponentRegistry::inst().valid(i))
					EntityVideoComponentRegistry::inst().get(i).update(fromClient.data().entities[i], msec);

		for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
			if (ScreenVideoComponentRegistry::inst().valid(i))
				ScreenVideoComponentRegistry::inst().get(i).update(msec);

		end();
	}
	
	present();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

