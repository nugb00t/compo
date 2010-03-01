#pragma once

#include "factories.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameEntityFactory : public engine::EntityFactory {
public:
	enum GameEntities {
		ENTITY_ORB,

		MAX_ENTITIES
	};

public:
	// interface: EntityFactory
	virtual engine::LogicComponent* createLogicComponent(const uint type);
	virtual engine::VideoComponent* createVideoComponent(const uint type);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameScreenFactory : public engine::ScreenFactory {
public:
	enum GameScreens {
		SCREEN_THREAD_PROFILER,
		SCREEN_HUD,

		MAX_SCREENS
	};

public:
	// interface: EntityFactory
	//virtual engine::LogicComponent* createLogicComponent(const uint type);
	virtual engine::ScreenVideoComponent* createVideoComponent(const uint type);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
