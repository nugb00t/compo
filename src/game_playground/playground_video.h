#pragma once

#include "video/video.h"
#include "video/video_impl.h"
#include "video/video_component.h"

#include "server/server_data.h"

#include "playground_factories.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameVideo : public engine::Video {
public:
	GameVideo() : initialized_(false) {}
	
protected:
	// interface: engine::Video
	virtual void doUpdate();

protected:
	boost::scoped_ptr<engine::OrthoCamera> orthoCamera_;	// for screens
	boost::scoped_ptr<engine::ProjCamera> projCamera_;		// for entities

	boost::scoped_ptr<engine::VideoComponent> entities_[engine::ServerState::MAX_ENTITIES];
	
	boost::scoped_ptr<engine::ScreenVideoComponent> screens_[GameScreenFactory::MAX_SCREENS];
	
	bool initialized_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}