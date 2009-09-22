#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "mesh_dx.h"
#include "video_system_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const D3DVERTEXELEMENT9 MeshDX::Vertex::Elements[] = {
	// stream, offset, type, method, usage, usage index
	{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
//	{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{ 0, 16, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	D3DDECL_END()
};

const MeshDX::Vertex MeshDX::vertices_[] = {
	{ Vector3(-.5f, -.5f, 0.f), 0xffff0000, Vector2(0.f, 1.f) },
	{ Vector3(-.5f,  .5f, 0.f), 0xff00ffff, Vector2(0.f, 0.f) },
	{ Vector3( .5f,  .5f, 0.f), 0xff00ff00, Vector2(1.f, 0.f) },
	{ Vector3( .5f, -.5f, 0.f), 0xff00ffff, Vector2(1.f, 1.f) },
};

const short MeshDX::indices_[] = {
	//0, 1, 2,
	//2, 3, 0
	0, 2, 1,
	3, 2, 0
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshDX::MeshDX()
: vertexDecl_(NULL), vertexBuffer_(NULL), indexBuffer_(NULL) {
	// vertex buffer
	CHECKED_D3D_CALL(VideoDX::inst().device().CreateVertexBuffer(sizeof(vertices_), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));

	void* locked;
	CHECKED_D3D_CALL(vertexBuffer_->Lock(0, 0, &locked, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
	::memcpy(locked, vertices_, sizeof(vertices_));
	CHECKED_D3D_CALL(vertexBuffer_->Unlock());

	// index buffer
	CHECKED_D3D_CALL(VideoDX::inst().device().CreateIndexBuffer(sizeof(indices_), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));

	CHECKED_D3D_CALL(indexBuffer_->Lock(0, 0, &locked, 0));
	::memcpy(locked, &indices_, sizeof(indices_));
	CHECKED_D3D_CALL(indexBuffer_->Unlock());

	// vertex decl
	CHECKED_D3D_CALL(VideoDX::inst().device().CreateVertexDeclaration(Vertex::Elements, &vertexDecl_));

	// texture
	texture_ = VideoDX::inst().createTexture();
	assert(texture_);
	CHECKED_CALL(texture_->load(_T("textures/myself.bmp")));

	// effect
	effect_ = VideoDX::inst().createEffect();
	assert(effect_);
	CHECKED_CALL(effect_->load(_T("fx/simple.h")));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshDX::~MeshDX() {
	if (vertexBuffer_)
		vertexBuffer_->Release();

	if (indexBuffer_)
		indexBuffer_->Release();

	if (vertexDecl_)
		vertexDecl_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshDX::draw(const Matrix44& view_proj) {
	//CHECKED_D3D_CALL(VideoDX::inst().device().SetTransform(D3DTS_WORLD, transform_.data()));

	CHECKED_D3D_CALL(VideoDX::inst().device().SetStreamSource(0, vertexBuffer_, 0, sizeof(Vertex)));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetIndices(indexBuffer_));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetVertexDeclaration(vertexDecl_));

	texture_->activate(0);

	Matrix44 wvp = transform_;
	wvp *= view_proj;
	effect_->activate(wvp);

	CHECKED_D3D_CALL(VideoDX::inst().device().DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, sizeof(vertices_) / sizeof(Vertex), 0, sizeof(indices_) / 3 / sizeof(short)));

	effect_->deactivate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECTX
