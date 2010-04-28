#include "stdafx.h"

#include "playground_video.h"

#include "core/sync.h"
#include "filesystem/files.h"

#include "game.h"

#include "entities/orb_video.h"
#include "entities/ball_video.h"
#include "screens/thread_profiler_video.h"
#include "screens/hud_video.h"

using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameVideo::initialize(engine::Video& video) {
	orthoCamera_.reset(video.createOrthoCamera());
	projCamera_.reset(video.createProjCamera());

	for (uint i = 0; i < GameFactory::MAX_ENTITIES; ++i) {
		entities_[i].reset(createVideoComponent(i));
		entities_[i]->initialize(video);
	}

	for (uint i = 0; i < GameFactory::MAX_SCREENS; ++i) {
		screens_[i].reset(createScreenVideoComponent(i));
		screens_[i]->initialize(video);
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameVideo::update(engine::Video& video) {
	// cameras
	orthoCamera_->update();
	projCamera_->update();

	// entities
	engine::Sync::ClientToVideo::Readable fromClient(engine::Sync::inst().clientToVideo);
	if (fromClient)
		for (uint i = 0; i < GameFactory::MAX_ENTITIES; ++i)
			if (entities_[i])
				entities_[i]->draw(video, fromClient.data().entities[i], projCamera_->view_projection());

	// screens
	for (uint i = 0; i < GameFactory::MAX_SCREENS; ++i)
		if (screens_[i])
			screens_[i]->draw(video, orthoCamera_->view_projection());

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameVideo::terminate() {
	orthoCamera_.reset();
	projCamera_.reset();

	for (uint i = 0; i < GameFactory::MAX_ENTITIES; ++i)
		entities_[i].reset();

	for (uint i = 0; i < GameFactory::MAX_SCREENS; ++i)
		screens_[i].reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

engine::VideoComponent* GameVideo::createVideoComponent(const uint type) {
	switch (type) {
		case GameFactory::ENTITY_ORB:
			return new OrbVideo;
			break;
		case GameFactory::ENTITY_BALL:
			return new BallVideo;
			break;
		default:
			assert(false);
			return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

engine::ScreenVideoComponent* GameVideo::createScreenVideoComponent(const uint type) {
	switch (type) {
		case GameFactory::SCREEN_THREAD_PROFILER:
			return new ThreadProfilerVideo;
			break;
		case GameFactory::SCREEN_HUD:
			return new HUDVideo;
			break;
		default:
			assert(false);
			return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
