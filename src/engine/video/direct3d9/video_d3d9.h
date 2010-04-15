#pragma once

#ifdef VIDEO_DIRECT3D9

#include "../video.h"

// factory-created objects
#include "camera_d3d9.h"

#include "video_assets_d3d9.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoD3D9 : public Video {
	static const uint MAX_VERTEX_DECL_ELEMS = 8;
	static const uint ASSET_POOL_SIZE = 1024;		// kB

	static const D3DVERTEXELEMENT9 VERTEX_DECL_ELEMS[VERTEX_DECL_COUNT][MAX_VERTEX_DECL_ELEMS];

public:
	static const TCHAR* EFFECT_PATHS[EFFECT_COUNT];
	static const VertexType EFFECT_VERTEX_DECLS[EFFECT_COUNT];

public:
	VideoD3D9();
	
	// interface: Video
	virtual bool initialize();
	virtual void terminate();

	virtual void clear();
	virtual bool begin();
	virtual void end();
	virtual void present();

	// assets
	virtual const uint addTexture(const TCHAR* const path) { return assets_.addTexture(path); }
	virtual void draw(DynamicMesh& mesh, const VertexType vertexType, const EffectType effect,
					  const TextureUniform* const texUniforms, const uint textureCount,
					  //const void* const uniforms, const uint uniformCount,
					  const Matrix44& transform);

	// object factory
	virtual ProjCamera* createProjCamera() { return new ProjectionCameraD3D9; }
	virtual OrthoCamera* createOrthoCamera() { return new OrthoCameraD3D9; }

	virtual DynamicMesh* createMesh(const uint vertexSize, const uint vertexCapacity, const uint indexCapacity);

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

	VideoAssetsD3D9 assets_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif