#pragma once

#include "server/server_data.h"
#include "game.h"
#include "video/video_component.h"
#include "playground_game.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameVideo : public engine::GameVideo {
	static const uint POOL_SIZE = 1024;

public:
	GameVideo() : pool_(POOL_SIZE) {}

	// interface: engine::GameVideo
	virtual bool initialize(engine::Video& video);
	virtual bool update(engine::Video& video);
	virtual void terminate();

private:
	virtual engine::VideoComponent* createVideoComponent(const uint type);
	virtual engine::ScreenVideoComponent* createScreenVideoComponent(const uint type);

private:
	boost::scoped_ptr<engine::OrthoCamera> orthoCamera_;	// for screens
	boost::scoped_ptr<engine::ProjCamera> projCamera_;		// for entities

	boost::scoped_ptr<engine::VideoComponent> entities_[GameFactory::MAX_ENTITIES];
	
	boost::scoped_ptr<engine::ScreenVideoComponent> screens_[GameFactory::MAX_SCREENS];

	kaynine::MemoryPool pool_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
