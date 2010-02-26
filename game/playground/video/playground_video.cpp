#include "stdafx.h"

#include "playground_video.h"

#include "engine.h"
#include "game.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameVideo::GameVideo() 
: screen_(NULL), hud_(NULL) {
	memset(&registry_, 0, sizeof(registry_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameVideo::doUpdate() {
	// TEMP
	if (!registry_[0])
		registry_[0] = g_game.entityFactory->createVideoComponent(0);		// 0 is a hack!

	if (!screen_)
		screen_ = g_game.screenFactory->createVideoComponent(0);		// 0 is a hack!

	if (!hud_)
		hud_ = g_game.screenFactory->createVideoComponent(1);		// 0 is a hack!
	// TEMP

	g_engine.videoImpl->orthoCamera().update();
	g_engine.videoImpl->projCamera().update();

	//screen_->draw();
	hud_->draw();

	Sync::ClientToVideo::Readable fromClient(g_engine.sync->clientToVideo);
	if (fromClient)
		for (uint i = 0; i < ServerState::MAX_ENTITIES; ++i)
			if (registry_[i])
				registry_[i]->draw(fromClient.data().entities[i]);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
