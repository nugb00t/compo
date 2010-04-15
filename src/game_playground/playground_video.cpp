#include "stdafx.h"

#include "playground_video.h"
#include "playground_factories.h"

#include "core/sync.h"
#include "filesystem/resources.h"

#include "game.h"

using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameVideo::initialize(engine::Video& video,
						   engine::VideoFactory& videoFactory,
						   engine::ScreenVideoFactory& screenVideoFactory) {
	orthoCamera_.reset(video.createOrthoCamera());
	projCamera_.reset(video.createProjCamera());

	for (uint i = 0; i < PlaygroundGame::MAX_ENTITIES; ++i) {
		entities_[i].reset(videoFactory.create(i));
		entities_[i]->initialize(video);
	}

	for (uint i = 0; i < PlaygroundGame::MAX_SCREENS; ++i) {
		screens_[i].reset(screenVideoFactory.create(i));
		screens_[i]->initialize(video);
	}

	//engine::Resources::inst().add(_T("main/fonts/bureau_20_o_0.dds"), pool_);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameVideo::update(engine::Video& video) {
	// cameras
	orthoCamera_->update();
	projCamera_->update();

	// entities
	engine::Sync::ClientToVideo::Readable fromClient(engine::Sync::inst().clientToVideo);
	if (fromClient)
		for (uint i = 0; i < PlaygroundGame::MAX_ENTITIES; ++i)
			if (entities_[i])
				entities_[i]->draw(video, fromClient.data().entities[i], projCamera_->view_projection());

	// screens
	for (uint i = 0; i < PlaygroundGame::MAX_SCREENS; ++i)
		screens_[i]->draw(video, orthoCamera_->view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
