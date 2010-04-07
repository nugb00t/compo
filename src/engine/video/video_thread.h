#pragma once

#include "video/video.h"
#include "game_factories.h"
#include "game_video.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoThread : public kaynine::ThreadObject {
public:
	VideoThread(Video* const video,
				GameVideo* const gameVideo,
				VideoFactory* const videoFactory,
				ScreenVideoFactory* const screenVideoFactory)
		: video_(video),
		  gameVideo_(gameVideo),
		  videoFactory_(videoFactory),
		  screenVideoFactory_(screenVideoFactory) {}

    // interface: kaynine::PulseThreadObject
	virtual bool initialize();
	virtual bool update();
	virtual void terminate();

public:
	Video* const video_;
	GameVideo* const gameVideo_;

	VideoFactory* const videoFactory_;
	ScreenVideoFactory* const screenVideoFactory_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
