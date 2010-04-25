#pragma once

#ifdef VIDEO_DIRECT3D9
#include "video/direct3d9/video_d3d9.h"
#endif

#include "game_factories.h"
#include "game_video.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoThread : public kaynine::ThreadObject {
public:
	VideoThread(GameVideo& gameVideo,
				VideoFactory& videoFactory,
				ScreenVideoFactory& screenVideoFactory)
		: gameVideo_(gameVideo),
		  videoFactory_(videoFactory),
		  screenVideoFactory_(screenVideoFactory) {}

    // interface: kaynine::ThreadObject
	virtual bool initialize();
	virtual bool update();
	virtual void terminate();

public:
	boost::scoped_ptr<Video> video_;

	GameVideo& gameVideo_;
	VideoFactory& videoFactory_;
	ScreenVideoFactory& screenVideoFactory_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
