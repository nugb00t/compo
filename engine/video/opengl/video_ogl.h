#ifndef VIDEO_OGL_INCLUDED
#define VIDEO_OGL_INCLUDED

#include "video/video_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoOGL : public Video {
public:
	VideoOGL();
	~VideoOGL();

	// interface: Callable
	virtual void operator()();

	// interface: Video
	virtual bool startup();
	virtual void shutdown();

	virtual void clear();
	virtual void flush();

	virtual void setOrthogonalView();
	virtual void draw(const DynamicMesh& mesh);
	virtual void drawTest();

	// window
	void reshape(const unsigned width, const unsigned height);

private:
    bool init();
	bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits, BYTE samples);

private:
	HGLRC	context_;
	float	aspect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
