#include "stdafx.h"

#include "video.h"
#include "video_component.h"

#include "engine.h"
#include "game.h"

#include "core/sync.h"
#include "core/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Video::Video() { 
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
		registry_[0] = g_game.entityFactory->createVideoComponent(0);
	// TEMP

	clear();

	if (begin()) {
		camera_->update();

		Sync::ClientToVideo::Readable fromClient(g_engine.sync->clientToVideo);
		if (fromClient && fromClient.age())
			::OutputDebugString(_T("Video::update(): failed to open Client package\n"));

		if (fromClient)
		for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
			if (registry_[i])
				registry_[i]->draw(fromClient.data().entities[i]);

		//for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
		//	if (ScreenVideoComponentRegistry::inst().valid(i))
		//		ScreenVideoComponentRegistry::inst().get(i).update();

		end();
	}
	
	present();

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

