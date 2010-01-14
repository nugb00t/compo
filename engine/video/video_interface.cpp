#include "stdafx.h"

#include "video_interface.h"

#include "core/sync.h"
#include "core/profiler.h"
#include "window/window_interface.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoInterface::initialize(Params* params) {
    assert(params && params->registry);
    registry_ = params->registry;

    camera_ = createCamera();
    return Video::inst().startup(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoInterface::update() {
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

