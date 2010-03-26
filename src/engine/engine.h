#pragma once

#ifdef PLATFORM_WIN51
#include "input/win51/input_w51.h"
#include "system/win51/system_loop_w51.h"
#include "window/win51/window_w51.h"
#else
#include "input/input.h"
#include "system/system_loop.h"
#include "window/window.h"
#endif

#ifdef VIDEO_DIRECT3D9
#include "video/direct3d9/video_d3d9.h"
#endif

#include "client/local_client.h"

#include "core/sync.h"
#include "core/time.h"

#include "utility/profiler.h"
#include "filesystem/resources.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Engine : public kaynine::Singleton<Engine> {

#ifdef PLATFORM_WIN51
	const boost::scoped_ptr<InputW51> inputW51;
	const boost::scoped_ptr<SystemLoopW51> systemLoopW51;
	const boost::scoped_ptr<WindowW51> windowW51;
#endif

#ifdef VIDEO_DIRECT3D9
	const boost::scoped_ptr<VideoD3D9> videoD3D9;
#endif

	Input* const input;
	SystemLoop* const systemLoop;
	Window* const window;

	VideoImpl* const video;

	const boost::scoped_ptr<LocalClient> localClient;
	const boost::scoped_ptr<Profiler> profiler;
	const boost::scoped_ptr<Time> time;
	const boost::scoped_ptr<Resources> resources;

	Engine() :
#ifdef PLATFORM_WIN51
	inputW51(new InputW51),
		input(inputW51.get()), 
		systemLoopW51(new SystemLoopW51),
		systemLoop(systemLoopW51.get()),
		windowW51(new WindowW51),
		window(windowW51.get()),
#endif
#ifdef VIDEO_DIRECT3D9
		videoD3D9(new VideoD3D9), 
		video(videoD3D9.get()), 
#endif
		localClient(new LocalClient),
		profiler(new Profiler),
		time(new Time),
		resources(new Resources)
	{}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
