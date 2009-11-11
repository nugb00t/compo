#ifndef VIDEO_D3D9_INCLUDED
#define VIDEO_D3D9_INCLUDED

#include "video/video_interface.h"

// factory-created objects
#include "camera_d3d9.h"
#include "mesh_d3d9.h"
#include "effect_d3d9.h"
#include "texture_d3d9.h"
#include "vertex_decl_d3d9.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<class VideoD3D9> VideoDX;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoD3D9 : public VideoInterface {
public:
    VideoD3D9::VideoD3D9() : d3d_(NULL), device_(NULL) { VideoDX::set(*this); }

	~VideoD3D9();

	// interface: VideoInterface
	virtual bool startup();
	virtual void shutdown();

	virtual void clear();
	virtual bool begin();
	virtual void end();
	virtual void present();

	// object factory
	virtual CameraPtr createCamera() { return new CameraD3D9; }
	virtual MeshPtr createMesh(EffectPtr effect) { return new MeshD3D9(effect); }
	virtual EffectPtr createEffect(const TCHAR* const path, const VertexDeclPtr vertexDecl) { return new EffectD3D9(path, vertexDecl); }
	virtual TexturePtr createTexture(const TCHAR* const path) { return new TextureD3D9(path); }

	virtual VertexDeclPtr getVertexDecl(const VertexDecl::Type type) { return VertexDeclD3D9::get(type); }

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

}

#endif
