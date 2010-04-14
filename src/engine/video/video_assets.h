#pragma once

#include "../video.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoAssets {
public:
	virtual void reset() = 0;
	virtual const uint addTexture(const TCHAR* const path) = 0;
	virtual void update(Video& video) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
