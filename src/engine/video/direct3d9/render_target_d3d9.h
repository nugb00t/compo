#pragma once

#ifdef VIDEO_DIRECT3D9

#include "../video.h"

#include "camera_d3d9.h"
#include "mesh_d3d9.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RenderTargetD3D9 {
	typedef Video::PosTex RenderVertex;

	static const D3DCOLOR CLEAR_COLOR = D3DCOLOR_XRGB(127, 127, 127);

	static const RenderVertex VERTICES[4];
	static const u16 INDICES[6];

public:
	RenderTargetD3D9(IDirect3DDevice9* device, IDirect3DVertexDeclaration9* decl, ID3DXEffect* effect);
	~RenderTargetD3D9();
	
	void begin();
	void end();
	void draw();

private:
	IDirect3DDevice9* device_;
	IDirect3DVertexDeclaration9* decl_;
	ID3DXEffect* effect_;

	ID3DXRenderToSurface* target_;
	IDirect3DTexture9* texture_;
	IDirect3DSurface9* surface_;
	StaticMeshD3D9 mesh_;
	OrthoCameraD3D9 camera_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif