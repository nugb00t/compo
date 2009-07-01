#ifndef VIDEO_SYSTEM_DX_INCLUDED
#define VIDEO_SYSTEM_DX_INCLUDED

#include "video/video_system.h"

// factory-created objects
#include "camera_dx.h"
#include "mesh_dx.h"
#include "texture_dx.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoSystemDX : public VideoSystem {
public:
	VideoSystemDX();
	~VideoSystemDX();

	// interface: Updatable
	virtual bool update(const float dt);

	// interface: VideoSystem
	virtual bool startup();
	virtual void shutdown();

	virtual bool init();

	virtual CameraPtr createCamera() { return new CameraDX; }
	virtual MeshPtr createMesh() { return new MeshDX; }
	virtual TexturePtr createTexture() { return new TextureDX; }

	// own
	IDirect3DDevice9& device() { return *device_; }

	// window
	void reshape(const unsigned width, const unsigned height);

private:

private:
	IDirect3D9* d3d_;
	IDirect3DDevice9* device_;

	CameraPtr camera_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<VideoSystemDX> VideoDX;

}

#endif
