#pragma once

#include "video/video.h"
#include "game_factories.h"
#include "game_video.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoThread : public kaynine::PulseThreadObject {
	static const uint PERIOD = 16;
	static const uint DELAY = 8 * 10;

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

	virtual const uint period() const { return PERIOD; }	// *1 milliseconds
	virtual const uint delay() const  { return DELAY;  }	// *100 nanoseconds

public:
	Video* const video_;
	GameVideo* const gameVideo_;

	VideoFactory* const videoFactory_;
	ScreenVideoFactory* const screenVideoFactory_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
