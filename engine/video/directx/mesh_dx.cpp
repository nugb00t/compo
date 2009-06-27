#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "mesh_dx.h"

#include "video_system_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const MeshDX::Vertex MeshDX::vertices_[] = {
	//{ Vector3(150.0f,  50.0f, 0.5f), D3DCOLOR_XRGB(255,   0, 255), },
	//{ Vector3(250.0f, 250.0f, 0.5f), D3DCOLOR_XRGB(  0, 255,   0), },
	//{ Vector3( 50.0f, 250.0f, 0.5f), D3DCOLOR_XRGB(255, 255,   0), },
	{ Vector3(15.0f,  5.0f, 1.5f), D3DCOLOR_XRGB(255,   0, 255), },
	{ Vector3(25.0f, 25.0f, 1.5f), D3DCOLOR_XRGB(  0, 255,   0), },
	{ Vector3( 5.0f, 25.0f, 1.5f), D3DCOLOR_XRGB(255, 255,   0), },
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshDX::MeshDX()
: vb_(NULL) {
	CHECKED_D3D_CALL(VideoDX::get().device().CreateVertexBuffer(3 * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_DEFAULT, &vb_, NULL));

	VOID* buffer = NULL;
	CHECKED_D3D_CALL(vb_->Lock(0, sizeof(vertices_), (void**)&buffer, 0));

	memcpy(buffer, vertices_, sizeof(vertices_));
	CHECKED_D3D_CALL(vb_->Unlock());

	texture_ = VideoDX::get().createTexture();
	assert(texture_);

	CHECKED_CALL(texture_->load(_T("myself.bmp")));		// tga
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MeshDX::update(const float /*dt*/) {
	D3DXMatrixIdentity(&transform_);
	D3DXMatrixTranslation(&transform_, 0.0f, 0.0f, 0.0f);

	CHECKED_D3D_CALL(VideoDX::get().device().SetTransform(D3DTS_WORLD, &transform_));

	CHECKED_D3D_CALL(VideoDX::get().device().SetStreamSource(0, vb_, 0, sizeof(Vertex)));
	CHECKED_D3D_CALL(VideoDX::get().device().SetFVF(Vertex::FVF));
	CHECKED_D3D_CALL(VideoDX::get().device().DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1));

	// TEMP
	//texture_->update();
	// TEMP

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECTX
