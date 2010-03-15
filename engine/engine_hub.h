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
	#include "video/direct3d9/video_impl_d3d9.h"
#endif

#include "logic/logic.h"
#include "core/profiler.h"
#include "core/sync.h"
#include "core/time.h"
#include "resources/resources.h"
#include "server/server.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Engine {
private:

#ifdef PLATFORM_WIN51
	const boost::scoped_ptr<InputW51> inputW51;
	const boost::scoped_ptr<SystemLoopW51> systemLoopW51;
	const boost::scoped_ptr<WindowW51> windowW51;
#endif

#ifdef VIDEO_DIRECT3D9
	const boost::scoped_ptr<VideoImplD3D9> videoImplD3D9;
#endif

public:
	Input* const input;
	SystemLoop* const systemLoop;
	Window* const window;
	
	VideoImpl* const videoImpl;

	const boost::scoped_ptr<Logic> logic;
	const boost::scoped_ptr<Profiler> profiler;
	const boost::scoped_ptr<Sync> sync;
	const boost::scoped_ptr<Time> time;
	const boost::scoped_ptr<Resources> resources;
	const boost::scoped_ptr<Server> server;

	const boost::scoped_ptr<kaynine::Trace> trace;

public:
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
		videoImplD3D9(new VideoImplD3D9), 
		videoImpl(videoImplD3D9.get()), 
#endif
		logic(new Logic),
		profiler(new Profiler),
		sync(new Sync),
		time(new Time),
		resources(new Resources),
		server(new Server),
		trace(new kaynine::Trace)
		{}

#ifdef PLATFORM_WIN51
	friend class SystemLoopW51;
#endif

#ifdef VIDEO_DIRECT3D9
	friend class EffectD3D9;
	friend class DynamicMeshD3D9;
	friend class TextureD3D9;
	friend class VertexDeclsD3D9;
#endif
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
