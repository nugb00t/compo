#pragma once

#include "game_factories.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LogicFactory : public engine::LogicFactory {
public:
	virtual engine::LogicComponent* create(const uint type);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoFactory : public engine::VideoFactory {
public:
	virtual engine::VideoComponent* create(const uint type);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreenVideoFactory : public engine::ScreenVideoFactory {
public:
	virtual engine::ScreenVideoComponent* create(const uint type);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
