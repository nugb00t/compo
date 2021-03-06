#pragma once

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
	void reshape(const uint width, const uint height);

private:
    bool init();
	bool choosePixelFormat(BYTE colorBits, BYTE alphaBits, BYTE depthBits, BYTE stencilBits, BYTE samples);

private:
	HGLRC	context_;
	float	aspect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
