#pragma once

#ifdef VIDEO_DIRECT3D9

#include "video/video.h"

// factory-created objects
#include "camera_d3d9.h"
#include "mesh_d3d9.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoD3D9 : public Video {

	static const uint MAX_VERTEX_DECL_ELEMS = 8;

	static const D3DVERTEXELEMENT9 VERTEX_DECL_ELEMS[VERTEX_DECL_COUNT][MAX_VERTEX_DECL_ELEMS];

public:
	static const TCHAR* EFFECT_PATHS[EFFECT_COUNT];
	static const VertexDeclType EFFECT_VERTEX_DECLS[EFFECT_COUNT];

public:
	VideoD3D9();
	
	// interface: Video
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

	virtual Effect* createEffect(const EffectType type);
	virtual Texture* createTexture(const TCHAR* const path);

	virtual void activateVertexDecl(const VertexDeclType type);

public:
	// own
	IDirect3DDevice9& device() { assert(device_); return *device_; }

	// window
	void reshape(const uint width, const uint height);

private:
	IDirect3D9* d3d_;
	IDirect3DDevice9* device_;
	
	IDirect3DVertexDeclaration9* vertexDecls_[VERTEX_DECL_COUNT];

	ID3DXEffect* effects_[EFFECT_COUNT];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif