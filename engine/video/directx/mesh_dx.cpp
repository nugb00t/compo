#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "mesh_dx.h"
#include "video_system_dx.h"

#pragma comment(lib, "winmm.lib")

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const MeshDX::Vertex MeshDX::vertices_[] = {
	{ Vector3(-.5f, -.5f, 0.f), /* 0xffff0000, */ Vector2(0.f, 1.f) },
	{ Vector3(-.5f,  .5f, 0.f), /* 0xff00ffff, */ Vector2(0.f, 0.f) },
	{ Vector3( .5f,  .5f, 0.f), /* 0xff00ff00, */ Vector2(1.f, 0.f) },
	{ Vector3( .5f, -.5f, 0.f), /* 0xff00ffff, */ Vector2(1.f, 1.f) },
};

const short MeshDX::indices_[] = {
	//0, 1, 2,
	//2, 3, 0
	0, 2, 1,
	3, 2, 0
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshDX::MeshDX()
: vertexBuffer_(NULL) {
	CHECKED_D3D_CALL(VideoDX::inst().device().CreateVertexBuffer(sizeof(vertices_), 0, Vertex::FVF, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));

	// vertex buffer
	void* buffer = NULL;
	CHECKED_D3D_CALL(vertexBuffer_->Lock(0, sizeof(vertices_), (void**)&buffer, 0));
	::memcpy(buffer, vertices_, sizeof(vertices_));
	CHECKED_D3D_CALL(vertexBuffer_->Unlock());

	// index buffer
	CHECKED_D3D_CALL(VideoDX::inst().device().CreateIndexBuffer(sizeof(indices_), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));

	buffer = NULL;
	CHECKED_D3D_CALL(indexBuffer_->Lock(0, 0, &buffer, 0));
	::memcpy(buffer, (void*) &indices_, sizeof(indices_));
	CHECKED_D3D_CALL(indexBuffer_->Unlock());

	texture_ = VideoDX::inst().createTexture();
	assert(texture_);

	CHECKED_CALL(texture_->load(_T("myself.bmp")));		// tga
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshDX::draw() {
	CHECKED_D3D_CALL(VideoDX::inst().device().SetTransform(D3DTS_WORLD, (const D3DMATRIX*)transform_.data()));

	texture_->activate(0);

	CHECKED_D3D_CALL(VideoDX::inst().device().SetStreamSource(0, vertexBuffer_, 0, sizeof(Vertex)));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetIndices(indexBuffer_));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetFVF(Vertex::FVF));
	CHECKED_D3D_CALL(VideoDX::inst().device().DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(vertices_) / sizeof(Vertex), 0, sizeof(indices_) / 3 / sizeof(short)));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECTX
