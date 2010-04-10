#pragma once

#ifdef PLATFORM_WIN51
#include "input/win51/input_w51.h"
#include "window/win51/window_w51.h"
#else
#include "input/input.h"
#include "window/window.h"
#endif

#ifdef VIDEO_DIRECT3D9
#include "video/direct3d9/video_d3d9.h"
#endif

#include "client/local_client.h"

#include "core/sync.h"
#include "core/time.h"

#include "utility/profiler.h"

#include "game.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Engine : public kaynine::Holder<Engine> {

#ifdef PLATFORM_WIN51
	const boost::scoped_ptr<InputW51> inputW51;
	const boost::scoped_ptr<WindowW51> windowW51;
#endif

#ifdef VIDEO_DIRECT3D9
	const boost::scoped_ptr<VideoD3D9> videoD3D9;
#endif

	Input* const input;
	Window* const window;
	Video* const video;

	const boost::scoped_ptr<LocalClient> localClient;
	const boost::scoped_ptr<Profiler> profiler;
	const boost::scoped_ptr<Time> time;

public:
	Engine(Game* game);

	void run();

private:
	const boost::scoped_ptr<Game> game_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
