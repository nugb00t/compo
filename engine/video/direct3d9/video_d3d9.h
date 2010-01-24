#ifndef VIDEO_D3D9_INCLUDED
#define VIDEO_D3D9_INCLUDED

#include "video/video.h"

// factory-created objects
#include "camera_d3d9.h"
#include "mesh_d3d9.h"
#include "effect_d3d9.h"
#include "texture_d3d9.h"
#include "vertex_decls_d3d9.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoD3D9 : public Video {
public:
    VideoD3D9::VideoD3D9() : d3d_(NULL), device_(NULL) {}
    ~VideoD3D9();

public:
	// interface: kaynine::ThreadObject
	virtual bool initialize();
	virtual void terminate();

	// interface: Video
	virtual void clear();
	virtual bool begin();
	virtual void end();
	virtual void present();

	// object factory
	virtual Camera* createCamera() { return new CameraD3D9; }
	virtual Mesh* createMesh(EffectPtr effect) { return new MeshD3D9(effect); }
	virtual Effect* createEffect(const TCHAR* const path, const VertexDecls::Type vertexDecl) { return new EffectD3D9(path, vertexDecl); }
	virtual Texture* createTexture(const TCHAR* const path) { return new TextureD3D9(path); }

	virtual void activateVertexDecl(const VertexDecls::Type type) { vertexDecls_.activate(type); }

public:
	// own
	IDirect3DDevice9& device() { return *device_; }

	// window
	void reshape(const unsigned width, const unsigned height);

private:
	IDirect3D9* d3d_;
	IDirect3DDevice9* device_;

	VertexDeclsD3D9 vertexDecls_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
