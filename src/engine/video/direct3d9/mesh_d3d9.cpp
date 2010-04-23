#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "mesh_d3d9.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StaticMeshD3D9::StaticMeshD3D9(const uint vertexSize, const uint vertexCount, const uint indexCount, const void* const vertices, const u16* const indices) 
:	StaticMesh(vertexSize, vertexCount, indexCount) {

	CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().CreateVertexBuffer(vertexSize_ * vertexCapacity_, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));
	void* vertexBuffer;
	CHECKED_D3D_CALL_A(vertexBuffer_->Lock(0, 0, &vertexBuffer, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
	memcpy(vertexBuffer, vertices, vertexSize * vertexCount);
	CHECKED_D3D_CALL_A(vertexBuffer_->Unlock());

	CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().CreateIndexBuffer(sizeof(short) * indexCapacity_, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));
	u16* indexBuffer;
	CHECKED_D3D_CALL_A(indexBuffer_->Lock(0, 0, (void**)&indexBuffer, 0));
	memcpy(indexBuffer, indices, sizeof(u16) * indexCount);
	CHECKED_D3D_CALL_A(indexBuffer_->Unlock());
}

//---------------------------------------------------------------------------------------------------------------------

void StaticMeshD3D9::streamBuffers(const uint vertexCount /*= 0*/, const uint primCount /*= 0*/) {
	assert(vertexBuffer_ && indexBuffer_);

	CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().SetStreamSource(0, vertexBuffer_, 0, vertexSize_));
	CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().SetIndices(indexBuffer_));
	CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
		vertexCount ? vertexCount : vertexCapacity_, 
		0, 
		primCount ? primCount : indexCapacity_ / 3));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicMeshD3D9::DynamicMeshD3D9(const uint vertexSize, const uint vertexCapacity, const uint indexCapacity)
:   DynamicMesh(vertexSize, vertexCapacity, indexCapacity),
    vertexBuffer_(NULL), indexBuffer_(NULL)
{
	assert(vertexSize && vertexCapacity && indexCapacity);

    CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().CreateVertexBuffer(vertexSize_ * vertexCapacity_, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));
    CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().CreateIndexBuffer(sizeof(short) * indexCapacity_, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));
}

//---------------------------------------------------------------------------------------------------------------------

DynamicMeshD3D9::~DynamicMeshD3D9() {
	if (vertexBuffer_)
		vertexBuffer_->Release();

	if (indexBuffer_)
		indexBuffer_->Release();
}

//---------------------------------------------------------------------------------------------------------------------

void DynamicMeshD3D9::lock() {
    CHECKED_D3D_CALL_A(vertexBuffer_->Lock(0, 0, &vertices_, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
    CHECKED_D3D_CALL_A(indexBuffer_->Lock(0, 0, (void**)&indices_, 0));
}

//---------------------------------------------------------------------------------------------------------------------

void DynamicMeshD3D9::unlock() {
    CHECKED_D3D_CALL_A(vertexBuffer_->Unlock());
    CHECKED_D3D_CALL_A(indexBuffer_->Unlock());
}

//---------------------------------------------------------------------------------------------------------------------

void DynamicMeshD3D9::streamBuffers(const uint vertexCount /*= 0*/, const uint primCount /*= 0*/) {
	assert(vertexBuffer_ && indexBuffer_);

	CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().SetStreamSource(0, vertexBuffer_, 0, vertexSize_));
	CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().SetIndices(indexBuffer_));
	CHECKED_D3D_CALL_A(Engine::inst().videoD3D9->device().DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
		vertexCount ? vertexCount : vertexCount_, 
		0, 
		primCount ? primCount : indexCount_ / 3));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECT3D9
