#ifndef VIDEO_SYSTEM_OGL_INCLUDED
#define VIDEO_SYSTEM_OGL_INCLUDED

#include "video/video_system.h"

namespace engine {

//=====================================================================================================================

class VideoSystemOGL : public VideoSystem {
public:
	// interface: Updatable
	virtual void update(const float dt);
};

//=====================================================================================================================

}

#endif
