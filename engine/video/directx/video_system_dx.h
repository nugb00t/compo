#ifndef VIDEO_SYSTEM_DX_INCLUDED
#define VIDEO_SYSTEM_DX_INCLUDED

#include "video/video_system.h"

// factory-created objects
#include "texture_dx.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoSystemDX : public VideoSystem {
public:
	VideoSystemDX();
	~VideoSystemDX();

	// interface: Callable
	virtual void operator()();

	// interface: VideoSystem
	virtual bool startup();
	virtual void shutdown();

	virtual bool init();

	virtual void setOrthogonalView();
	virtual void draw(const Mesh& mesh);
	virtual void drawTest();

	virtual TexturePtr createTexture() { return new TextureDX; }

	// own
	IDirect3DDevice9& device() { return *device_; }

	// window
	void reshape(const unsigned width, const unsigned height);

private:
	void update();

private:
	IDirect3D9* d3d_;
	IDirect3DDevice9* device_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<VideoSystemDX> VideoDX;

}

#endif
