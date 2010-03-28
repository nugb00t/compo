#include "stdafx.h"

#include "playground_video.h"
#include "playground_factories.h"

#include "engine.h"
#include "game.h"

using engine::Engine;
using engine::Game;
using engine::Sync;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameVideo::initialize(engine::Video* const video,
						   engine::VideoFactory* const videoFactory,
						   engine::ScreenVideoFactory* const screenVideoFactory) {
	orthoCamera_.reset(video->createOrthoCamera());
	projCamera_.reset(video->createProjCamera());

	for (uint i = 0; i < PlaygroundGame::MAX_ENTITIES; ++i)
		entities_[i].reset(videoFactory->create(i));

	for (uint i = 0; i < PlaygroundGame::MAX_SCREENS; ++i)
		screens_[i].reset(screenVideoFactory->create(i));

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameVideo::update(engine::Video* const video) {
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
