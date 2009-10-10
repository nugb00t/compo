#ifndef VIDEO_SYSTEM_DX_INCLUDED
#define VIDEO_SYSTEM_DX_INCLUDED

#include "video/video_system.h"

// factory-created objects
#include "camera_dx.h"
#include "mesh_dx.h"
#include "effect_dx.h"
#include "texture_dx.h"
#include "vertex_decl_dx.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoSystemDX : public VideoSystem {
public:
	VideoSystemDX();
	~VideoSystemDX();

	// interface: VideoSystem
	virtual bool startup();
	virtual void shutdown();

	virtual void clear();
	virtual bool begin();
	virtual void end();
	virtual void present();

	virtual bool init();

	// object factory
	virtual CameraPtr createCamera() { return new CameraDX; }
	virtual MeshPtr createMesh(EffectPtr effect) { return new MeshDX(effect); }
	virtual EffectPtr createEffect(const TCHAR* const path, const VertexDeclPtr vertexDecl, const TexturePtr texture) { return new EffectDX(path, vertexDecl, texture); }
	virtual TexturePtr createTexture(const TCHAR* const path) { return new TextureDX(path); }

	virtual VertexDeclPtr getVertexDecl(const VertexDecl::Type type) { return VertexDeclDX::get(type); }

	// own
	IDirect3DDevice9& device() { return *device_; }

	// window
	void reshape(const unsigned width, const unsigned height);

private:

private:
	IDirect3D9* d3d_;
	IDirect3DDevice9* device_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<VideoSystemDX> VideoDX;

}

#endif
