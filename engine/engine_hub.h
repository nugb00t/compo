#ifndef ENGINE_HUB_INCLUDED
#define ENGINE_HUB_INCLUDED

#ifdef PLATFORM_WIN51
	#include "input/win51/input_w51.h"
#else
	#include "input/input.h"
#endif

#include "video/video.h"
#ifdef VIDEO_DIRECT3D9
	#include "video/direct3d9/video_d3d9.h"
#endif

#ifdef PLATFORM_WIN51
	#include "window/win51/window_w51.h"
#else
	#include "window/window.h"
#endif

#include "logic/logic.h"
#include "core/profiler.h"
#include "core/sync.h"
#include "core/time.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Engine {
private:

#ifdef PLATFORM_WIN51
	const boost::scoped_ptr<InputW51> inputW51;
#endif

#ifdef VIDEO_DIRECT3D9
	const boost::scoped_ptr<VideoD3D9> videoD3D9;
#endif

#ifdef PLATFORM_WIN51
	const boost::scoped_ptr<WindowW51> windowW51;
#endif

public:
	Input* const input;
	Video* const video;
	Window* const window;

	const boost::scoped_ptr<Logic> logic;
	const boost::scoped_ptr<Profiler> profiler;
	const boost::scoped_ptr<Sync> sync;
	const boost::scoped_ptr<Time> time;

public:
	Engine() :
#ifdef PLATFORM_WIN51
		inputW51(new InputW51),
		input(inputW51.get()), 
#endif
#ifdef VIDEO_DIRECT3D9
		videoD3D9(new VideoD3D9), 
		video(videoD3D9.get()), 
#endif
#ifdef PLATFORM_WIN51
		windowW51(new WindowW51),
		window(windowW51.get()),
#endif
		logic(new Logic),
		profiler(new Profiler),
		sync(new Sync),
		time(new Time)
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

#endif
