#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "mesh_dx.h"

#include "video_system_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const MeshDX::Vertex MeshDX::vertices_[] = {
	{ Vector3(150.0f,  50.0f, 0.5f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), },
	{ Vector3(250.0f, 250.0f, 0.5f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), },
	{ Vector3( 50.0f, 250.0f, 0.5f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), },
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshDX::MeshDX()
: vb_(NULL) {
	DEBUG_ONLY(HRESULT res = )
	VideoDX::get().device().CreateVertexBuffer(3 * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_DEFAULT, &vb_, NULL);
	assert(res == D3D_OK);

	VOID* buffer = NULL;

	DEBUG_ONLY(res = )
	vb_->Lock(0, sizeof(vertices_), (void**)&buffer, 0);
	assert(res == D3D_OK);

	memcpy(buffer, vertices_, sizeof(vertices_));
	vb_->Unlock();

	texture_ = VideoDX::get().createTexture();
	assert(texture_);

	DEBUG_ONLY(bool ok = )
		texture_->load(_T("myself.bmp"));		// tga
	assert(ok);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MeshDX::update(const float /*dt*/) {
	D3DXMatrixIdentity(&transform_);
	D3DXMatrixTranslation(&transform_, 0.0f, 0.0f, 0.0f);

	DEBUG_ONLY(HRESULT res = )
		VideoDX::get().device().SetTransform(D3DTS_WORLD, &transform_);
	assert(res == D3D_OK);

	// tmp
	texture_->update();
	// tmp

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECTX
