#pragma once

#ifdef VIDEO_DIRECT3D9
#include "video/direct3d9/video_d3d9.h"
#endif

#include "game.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoThread : public kaynine::ThreadObject {
public:
	VideoThread(GameFactory& game, Window& window) : game_(game), window_(window) {}

    // interface: kaynine::ThreadObject
	virtual bool initialize();
	virtual bool update();
	virtual void terminate();

public:
	GameFactory& game_;
	Window& window_;
	
	boost::scoped_ptr<Video> video_;
	boost::scoped_ptr<GameVideo> gameVideo_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
