#include "stdafx.h"

#include "playground_video.h"

#include "engine.h"
#include "game.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameVideo::doUpdate() {
	if (!initialized_) {
		orthoCamera_.reset(Engine::inst().videoImpl->createOrthoCamera());
		projCamera_.reset(Engine::inst().videoImpl->createProjCamera());
		
		for (uint i = 0; i < GameEntityFactory::MAX_ENTITIES; ++i)
			entities_[i].reset(Game::inst().entityFactory->createVideoComponent(i));
	
		for (uint i = 0; i < GameScreenFactory::MAX_SCREENS; ++i)
			screens_[i].reset(Game::inst().screenFactory->createVideoComponent(i));
			
		initialized_ = true;
	}
	
	// cameras
	orthoCamera_->update();
	projCamera_->update();

	// entities
	Sync::ClientToVideo::Readable fromClient(Sync::inst().clientToVideo);
	if (fromClient)
		for (uint i = 0; i < ServerState::MAX_ENTITIES; ++i)
			if (entities_[i])
				entities_[i]->draw(fromClient.data().entities[i], projCamera_->view_projection());

	// screens
	for (uint i = 0; i < GameScreenFactory::MAX_SCREENS; ++i)
		screens_[i]->draw(orthoCamera_->view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
