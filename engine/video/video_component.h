#pragma once

#include "server/server_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoComponent {
public:
    virtual void draw(const ServerState::Entity& fromLogic, const Matrix44& view_projection) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreenVideoComponent {
public:
	virtual void draw(const Matrix44& view_projection) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
