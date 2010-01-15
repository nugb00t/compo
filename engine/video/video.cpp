#include "stdafx.h"

#include "video.h"

#include "window/window.h"

#include "core/sync.h"
#include "core/profiler.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Video::update() {
	clear();

	if (begin()) {
		camera_->update();

		Sync::ClientToVideo::Readable fromClient(Sync::inst().clientToVideo());
		if (fromClient)
			for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
				if (registry_->valid(i))
					registry_->get(i).update(fromClient.data().entities[i]);

		//for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
		//	if (ScreenVideoComponentRegistry::inst().valid(i))
		//		ScreenVideoComponentRegistry::inst().get(i).update();

		end();
	}
	
	present();

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

