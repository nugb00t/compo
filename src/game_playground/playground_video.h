#pragma once

#include "server/server_data.h"
#include "video/video_component.h"

#include "game_video.h"

#include "playground_game.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameVideo : public engine::GameVideo {
public:
	// interface: engine::GameVideo
	virtual bool initialize(engine::Video& video,
							engine::VideoFactory& videoFactory,
							engine::ScreenVideoFactory& screenVideoFactory);
	virtual void update(engine::Video& video);

protected:
	boost::scoped_ptr<engine::OrthoCamera> orthoCamera_;	// for screens
	boost::scoped_ptr<engine::ProjCamera> projCamera_;		// for entities

	boost::scoped_ptr<engine::VideoComponent> entities_[PlaygroundGame::MAX_ENTITIES];
	
	boost::scoped_ptr<engine::ScreenVideoComponent> screens_[PlaygroundGame::MAX_SCREENS];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
