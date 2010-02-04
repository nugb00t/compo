#include "stdafx.h"

#include "video.h"
#include "video_component.h"

#include "engine.h"
#include "game.h"

#include "core/sync.h"
#include "core/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Video::Video() : screen_(NULL) { 
	memset(&registry_, 0, sizeof(registry_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

kaynine::Event& Video::quit() { 
	return g_engine.sync->quit; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Video::update() {
	// TEMP
	if (!registry_[0])
		registry_[0] = g_game.entityFactory->createVideoComponent(0);		// 0 is a hack!
	
	if (!screen_)
		screen_ = g_game.screenFactory->createVideoComponent(0);		// 0 is a hack!
	// TEMP

	Profiler::StopWatch stopWatch(Profiler::VIDEO);

	clear();

	if (begin()) {
		orthoCamera_->update();
		projCamera_->update();

		screen_->draw();

		Sync::ClientToVideo::Readable fromClient(g_engine.sync->clientToVideo);
		if (fromClient)
			for (uint i = 0; i < ServerState::MAX_ENTITIES; ++i)
				if (registry_[i])
					registry_[i]->draw(fromClient.data().entities[i]);

		end();
	}
	
	present();

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

