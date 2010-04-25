#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "mesh_d3d9.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StaticMeshD3D9::StaticMeshD3D9(IDirect3DDevice9* device, const uint vertexSize, const void* const vertices, const uint vertexCount, const u16* const indices, const uint indexCount) 
:	StaticMesh(vertexSize, vertexCount, indexCount),
	device_(device), vertexBuffer_(NULL), indexBuffer_(NULL)
{
	CHECKED_D3D_CALL_A(device_->CreateVertexBuffer(vertexSize_ * vertexCount_, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));
	CHECKED_D3D_CALL_A(device_->CreateIndexBuffer(sizeof(short) * indexCount_, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));

	void* vertexBuffer;
	CHECKED_D3D_CALL_A(vertexBuffer_->Lock(0, 0, &vertexBuffer, D3DLOCK_NOSYSLOCK));
	memcpy(vertexBuffer, vertices, vertexSize * vertexCount);
	CHECKED_D3D_CALL_A(vertexBuffer_->Unlock());

	u16* indexBuffer;
	CHECKED_D3D_CALL_A(indexBuffer_->Lock(0, 0, (void**)&indexBuffer, D3DLOCK_NOSYSLOCK));
	memcpy(indexBuffer, indices, sizeof(u16) * indexCount);
	CHECKED_D3D_CALL_A(indexBuffer_->Unlock());
}

//---------------------------------------------------------------------------------------------------------------------

StaticMeshD3D9::~StaticMeshD3D9() {
	if (vertexBuffer_)
		vertexBuffer_->Release();

	if (indexBuffer_)
		indexBuffer_->Release();
}

//---------------------------------------------------------------------------------------------------------------------

void StaticMeshD3D9::streamBuffers(const uint vertexCount /*= 0*/, const uint primCount /*= 0*/) {
	assert(vertexBuffer_ && indexBuffer_);

	CHECKED_D3D_CALL_A(device_->SetStreamSource(0, vertexBuffer_, 0, vertexSize_));
	CHECKED_D3D_CALL_A(device_->SetIndices(indexBuffer_));
	CHECKED_D3D_CALL_A(device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
		vertexCount ? vertexCount : vertexCount_, 
		0, 
		primCount ? primCount : indexCount_ / 3));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicMeshD3D9::DynamicMeshD3D9(IDirect3DDevice9* device, const uint vertexSize, const uint vertexCapacity, const uint indexCapacity)
:	DynamicMesh(vertexSize, vertexCapacity, indexCapacity),
	device_(device), vertexBuffer_(NULL), indexBuffer_(NULL)
{
    CHECKED_D3D_CALL_A(device_->CreateVertexBuffer(vertexSize_ * vertexCapacity_, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));
    CHECKED_D3D_CALL_A(device_->CreateIndexBuffer(sizeof(short) * indexCapacity_, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));
}

//---------------------------------------------------------------------------------------------------------------------

DynamicMeshD3D9::~DynamicMeshD3D9() {
	if (vertexBuffer_)
		vertexBuffer_->Release();

	if (indexBuffer_)
		indexBuffer_->Release();
}

//---------------------------------------------------------------------------------------------------------------------

void* DynamicMeshD3D9::vertices() {
	void* vertices;
	CHECKED_D3D_CALL_A(vertexBuffer_->Lock(0, 0, &vertices, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
	return vertices;
}

//---------------------------------------------------------------------------------------------------------------------

u16* DynamicMeshD3D9::indices() {
	u16* indices;
    CHECKED_D3D_CALL_A(indexBuffer_->Lock(0, 0, (void**)&indices, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
	return indices;
}

//---------------------------------------------------------------------------------------------------------------------

void DynamicMeshD3D9::unlock() {
    CHECKED_D3D_CALL_A(vertexBuffer_->Unlock());
    CHECKED_D3D_CALL_A(indexBuffer_->Unlock());
}

//---------------------------------------------------------------------------------------------------------------------

void DynamicMeshD3D9::streamBuffers(const uint vertexCount /*= 0*/, const uint primCount /*= 0*/) {
	assert(vertexBuffer_ && indexBuffer_);

	CHECKED_D3D_CALL_A(device_->SetStreamSource(0, vertexBuffer_, 0, vertexSize_));
	CHECKED_D3D_CALL_A(device_->SetIndices(indexBuffer_));
	CHECKED_D3D_CALL_A(device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
		vertexCount ? vertexCount : vertexCount_, 
		0, 
		primCount ? primCount : indexCount_ / 3));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif