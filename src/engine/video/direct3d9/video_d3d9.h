#pragma once

#include "video/video.h"

// factory-created objects
#include "camera_d3d9.h"
#include "mesh_d3d9.h"
#include "effect_d3d9.h"
#include "texture_d3d9.h"
#include "vertex_decls_d3d9.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoD3D9 : public VideoImpl {
public:
    VideoD3D9::VideoD3D9() : d3d_(NULL), device_(NULL) {}
    ~VideoD3D9();

public:
	// interface: VideoImpl
	virtual bool initialize();
	virtual void terminate();

	virtual void clear();
	virtual bool begin();
	virtual void end();
	virtual void present();

	// object factory
	virtual ProjCamera* createProjCamera() { return new ProjectionCameraD3D9; }
	virtual OrthoCamera* createOrthoCamera() { return new OrthoCameraD3D9; }

	virtual DynamicMesh* createMesh(engine::Effect& effect, const uint vertexSize, const uint vertexCapacity, const uint indexCapacity) { return new DynamicMeshD3D9(effect, vertexSize, vertexCapacity, indexCapacity); }

	virtual Effect* createEffect(const VertexDecls::Type vertexDecl) { return new EffectD3D9(vertexDecl); }
	virtual Texture* createTexture(const TCHAR* const path);

	virtual void activateVertexDecl(const VertexDecls::Type type) { vertexDecls_.activate(type); }

public:
	// own
	IDirect3DDevice9& device() { return *device_; }

	// window
	void reshape(const uint width, const uint height);

private:
	IDirect3D9* d3d_;
	IDirect3DDevice9* device_;

	VertexDeclsD3D9 vertexDecls_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
