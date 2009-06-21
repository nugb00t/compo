#ifndef VIDEO_SYSTEM_OGL_INCLUDED
#define VIDEO_SYSTEM_OGL_INCLUDED

#include "video/video_system.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoSystemOGL : public VideoSystem {
public:
	VideoSystemOGL();
	~VideoSystemOGL();

	// interface: Callable
	virtual void operator()();

	// interface: VideoSystem
	virtual bool startup();
	virtual void shutdown();

	virtual void clear();
	virtual bool init();
	virtual void flush();

	virtual void setOrthogonalView();
	virtual void draw(const Mesh& mesh);
	virtual void drawTest();

	// window
	void reshape(const unsigned width, const unsigned height);

private:
	bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits, BYTE samples);

private:
	HGLRC	context_;
	float	aspect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
