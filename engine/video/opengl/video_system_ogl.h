#ifndef VIDEO_SYSTEM_OGL_INCLUDED
#define VIDEO_SYSTEM_OGL_INCLUDED

#include "video/video_system.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoSystemOGL : public VideoSystem {
public:
	VideoSystemOGL();
	~VideoSystemOGL();

	// interface: VideoSystem
	virtual bool startup();
	virtual void shutdown();

	virtual void clear();
	virtual bool init();
	virtual void flush();

	// window
	void reshape(int width, int height);

	// interface: VideoSystem
	virtual void setOrthogonalView();
	virtual void drawMesh(const Mesh& mesh);

private:
	bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits, BYTE samples);

private:
	HGLRC					context_;
	float					aspect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
