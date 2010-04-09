#pragma once

#include "video/video.h"
#include "game_factories.h"
#include "game_video.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoThread : public kaynine::ThreadObject {
public:
	VideoThread(Video& video,
				GameVideo& gameVideo,
				VideoFactory& videoFactory,
				ScreenVideoFactory& screenVideoFactory)
		: video_(video),
		  gameVideo_(gameVideo),
		  videoFactory_(videoFactory),
		  screenVideoFactory_(screenVideoFactory) {}

    // interface: kaynine::ThreadObject
	virtual bool initialize();
	virtual bool update();
	virtual void terminate();

public:
	Video& video_;
	GameVideo& gameVideo_;

	VideoFactory& videoFactory_;
	ScreenVideoFactory& screenVideoFactory_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
