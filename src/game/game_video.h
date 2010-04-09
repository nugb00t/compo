#pragma once

#include "video/video.h"
#include "game_factories.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameVideo {
public:
	virtual ~GameVideo() {}
	virtual bool initialize(engine::Video& video,
							engine::VideoFactory& videoFactory,
							engine::ScreenVideoFactory& screenVideoFactory) = 0;
	virtual void update(engine::Video& video) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
