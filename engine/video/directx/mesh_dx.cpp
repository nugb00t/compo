#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "mesh_dx.h"

#include "video_system_dx.h"

#pragma comment(lib, "winmm.lib")

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const MeshDX::Vertex MeshDX::vertices_[] = {
	{ D3DXVECTOR3( 5.0f,  5.0f, 1.5f), 0xffff0000, },
	{ D3DXVECTOR3(25.0f, 25.0f, 1.5f), 0xff00ff00, },
	{ D3DXVECTOR3( 5.0f, 25.0f, 1.5f), 0xff00ffff, },
	{ D3DXVECTOR3(25.0f,  5.0f, 1.5f), 0xff00ffff, },
};

const short MeshDX::indices_[] = {
	0, 1, 2,
	3, 1, 0
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshDX::MeshDX()
: vertexBuffer_(NULL) {
	CHECKED_D3D_CALL(VideoDX::get().device().CreateVertexBuffer(sizeof(vertices_), 0, Vertex::FVF, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));

	// vertex buffer
	void* buffer = NULL;
	CHECKED_D3D_CALL(vertexBuffer_->Lock(0, sizeof(vertices_), (void**)&buffer, 0));
	::memcpy(buffer, vertices_, sizeof(vertices_));
	CHECKED_D3D_CALL(vertexBuffer_->Unlock());

	// index buffer
	CHECKED_D3D_CALL(VideoDX::get().device().CreateIndexBuffer(sizeof(indices_), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));

	buffer = NULL;
	CHECKED_D3D_CALL(indexBuffer_->Lock(0, 0, &buffer, 0));
	::memcpy(buffer, (void*) &indices_, sizeof(indices_));
	CHECKED_D3D_CALL(indexBuffer_->Unlock());

	texture_ = VideoDX::get().createTexture();
	assert(texture_);

	CHECKED_CALL(texture_->load(_T("myself.bmp")));		// tga
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MeshDX::update(const float /*dt*/) {
	D3DXMatrixIdentity(&transform_);
	D3DXMatrixTranslation(&transform_, 0.0f, 0.0f, 0.0f);

	unsigned time = ::timeGetTime() % 1000;
	float angle = time * (2.0f * D3DX_PI) / 1000.0f;
	D3DXMatrixRotationY(&transform_, angle);

	CHECKED_D3D_CALL(VideoDX::get().device().SetTransform(D3DTS_WORLD, &transform_));

	CHECKED_D3D_CALL(VideoDX::get().device().SetStreamSource(0, vertexBuffer_, 0, sizeof(Vertex)));
	CHECKED_D3D_CALL(VideoDX::get().device().SetIndices(indexBuffer_));
	CHECKED_D3D_CALL(VideoDX::get().device().SetFVF(Vertex::FVF));
	CHECKED_D3D_CALL(VideoDX::get().device().DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(vertices_) / sizeof(Vertex), 0, sizeof(indices_) / 3 / sizeof(short)));

	// TEMP
	//texture_->update();
	// TEMP

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECTX
