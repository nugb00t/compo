#pragma once

#include "video/video.h"
#include "game_factories.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameVideo {
public:
	virtual bool initialize(engine::Video* const video,
							engine::VideoFactory* const videoFactory,
							engine::ScreenVideoFactory* const screenVideoFactory) = 0;
	virtual void update(engine::Video* const video) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
