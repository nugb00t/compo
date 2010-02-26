#pragma once

#include "server/server_data.h"

#include "video/video.h"
#include "video/video_component.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameVideo : public engine::Video {
public:
	GameVideo();
	
protected:
	// interface: engine::Video
	virtual void doUpdate();

protected:
	engine::VideoComponent* registry_[engine::ServerState::MAX_ENTITIES];

	engine::ScreenVideoComponent* screen_;
	engine::ScreenVideoComponent* hud_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
