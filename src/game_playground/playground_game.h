#pragma once

#include "game.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameFactory : public engine::GameFactory {
public:
	enum Entities {
		ENTITY_ORB,
		ENTITY_BALL,

		MAX_ENTITIES
	};

	enum Screens {
		SCREEN_THREAD_PROFILER,
		SCREEN_HUD,

		MAX_SCREENS
	};

public:
	// interface: engine::GameFactory
	virtual engine::GameLocalClient* createLocalClient();
	virtual engine::GameArbiter* createArbiter();
	virtual engine::GameFlow* createFlow();
	virtual engine::GameVideo* createVideo();
	virtual engine::LogicComponent* createLogicComponent(const uint type);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}