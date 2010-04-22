#include "stdafx.h"

#include "playground_factories.h"
#include "playground_game.h"

#include "entities/orb_logic.h"
#include "entities/orb_video.h"

#include "entities/ball_video.h"

#include "screens/thread_profiler_video.h"
#include "screens/hud_video.h"

using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

engine::LogicComponent* LogicFactory::create(const uint type) {
	switch (type) {
		case PlaygroundGame::ENTITY_ORB:
			return new OrbLogic;
			break;
		default:
			assert(false);
			return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

engine::VideoComponent* VideoFactory::create(const uint type) {
	switch (type) {
		case PlaygroundGame::ENTITY_ORB:
			return new OrbVideo;
			break;
		case PlaygroundGame::ENTITY_BALL:
			return new BallVideo;
			break;
		default:
			assert(false);
			return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

engine::ScreenVideoComponent* ScreenVideoFactory::create(const uint type) {
	switch (type) {
		case PlaygroundGame::SCREEN_THREAD_PROFILER:
			return new ThreadProfilerVideo;
			break;
		case PlaygroundGame::SCREEN_HUD:
			return new HUDVideo;
			break;
		default:
			assert(false);
			return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
