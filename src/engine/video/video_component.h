#pragma once

#include "server/server_data.h"
#include "video/video.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoComponent {
public:
	virtual ~VideoComponent() {};
	
	virtual void initialize(engine::Video& ) = 0;
	virtual void draw(engine::Video& video, const ServerState::Entity& fromLogic, const Matrix44& view_projection) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreenVideoComponent {
public:
	virtual ~ScreenVideoComponent() {};

	virtual void initialize(engine::Video& ) = 0;
	virtual void draw(engine::Video& video, const Matrix44& view_projection) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

