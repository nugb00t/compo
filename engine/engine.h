#ifndef ENGINE_INCLUDED
#define ENGINE_INCLUDED

#ifdef PLATFORM_WIN51
	#include "input/win51/input_w51.h"
#else
	#include "input/input.h"
#endif

#include "logic/logic.h"

#include "video/video.h"
#ifdef VIDEO_DIRECT3D9
	#include "video/direct3d9/video_d3d9.h"
#endif

#ifdef PLATFORM_WIN51
	#include "window/win51/window_w51.h"
#else
	#include "window/window.h"
#endif

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
		logic(new Logic)
		{}

#ifdef PLATFORM_WIN51
	friend class MessageSinkW51;
#endif

#ifdef VIDEO_DIRECT3D9
	friend class EffectD3D9;
	friend class MeshD3D9;
	friend class TextureD3D9;
	friend class VertexDeclD3D9;
#endif
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern Engine g_engine;

}

#endif
