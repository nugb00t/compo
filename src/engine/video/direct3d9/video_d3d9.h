#pragma once

#ifdef VIDEO_DIRECT3D9

#include "../video.h"

#include "system/window.h"

#include "render_target_d3d9.h"
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
	VideoD3D9(Window& window);
	
	// interface: Video
	virtual bool initialize();
	virtual void terminate();

	virtual void begin();
	virtual void end();

	// assets
	virtual const uint addTexture(const TCHAR* const path) { return assets_.addTexture(path); }

	// instancing:
	//
	// http://msdn.microsoft.com/en-us/library/bb173349(VS.85).aspx
	// http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter03.html
	// http://msdn.microsoft.com/en-us/library/bb174460(v=VS.85).aspx
	//
	// virtual void draw(Mesh& mesh);
	virtual void draw(Mesh& mesh, const VertexType vertexType, const EffectType effect,
					  const TextureUniform* const texUniforms, const uint textureCount,
					  const Matrix44& transform);

	// object factory
	virtual ProjCamera* createProjCamera() { return new ProjectionCameraD3D9; }
	virtual OrthoCamera* createOrthoCamera() { return new OrthoCameraD3D9; }

	virtual StaticMesh* createStaticMesh(const uint vertexSize, const void* const vertices, const uint vertexCount, const u16* const indices, const uint indexCount);
	virtual DynamicMesh* createDynamicMesh(const uint vertexSize, const uint vertexCapacity, const uint indexCapacity);

public:
	// own
	IDirect3DDevice9& device() { assert(device_); return *device_; }

	// window
	void reshape(const uint width, const uint height);

private:
	Window& window_;
	
	IDirect3D9* d3d_;
	IDirect3DDevice9* device_;
	
	IDirect3DVertexDeclaration9* vertexDecls_[VERTEX_DECL_COUNT];

	ID3DXEffect* effects_[EFFECT_COUNT];

	// render-to-texture
	//ID3DXRenderToSurface* renderTarget_;
	//IDirect3DTexture9* renderTexture_;
	//IDirect3DSurface9* renderSurface_;
	//boost::scoped_ptr<StaticMeshD3D9> renderMesh_;
	//OrthoCameraD3D9 renderCamera_;
	//typedef PosTex RenderVertex;
	boost::scoped_ptr<RenderTargetD3D9> target_;

	VideoAssetsD3D9 assets_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif