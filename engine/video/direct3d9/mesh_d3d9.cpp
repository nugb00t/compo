#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicMeshD3D9::DynamicMeshD3D9(Effect& effect, const uint vertexSize, const uint vertexCapacity, const uint indexCapacity)
:   DynamicMesh(effect, vertexSize, vertexCapacity, indexCapacity),
    vertexBuffer_(NULL), indexBuffer_(NULL)
{
	assert(vertexSize && vertexCapacity && indexCapacity);

    CHECKED_D3D_CALL(g_engine.videoImplD3D9->device().CreateVertexBuffer(vertexSize_ * vertexCapacity_, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));
    CHECKED_D3D_CALL(g_engine.videoImplD3D9->device().CreateIndexBuffer(sizeof(short) * indexCapacity_, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicMeshD3D9::~DynamicMeshD3D9() {
	if (vertexBuffer_)
		vertexBuffer_->Release();

	if (indexBuffer_)
		indexBuffer_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DynamicMeshD3D9::lock() {
    CHECKED_D3D_CALL(vertexBuffer_->Lock(0, 0, &vertices_, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
    CHECKED_D3D_CALL(indexBuffer_->Lock(0, 0, (void**)&indices_, 0));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DynamicMeshD3D9::unlock() {
    CHECKED_D3D_CALL(vertexBuffer_->Unlock());
    CHECKED_D3D_CALL(indexBuffer_->Unlock());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DynamicMeshD3D9::streamBuffers(const uint vertexCount, const uint primCount) {
	assert(vertexBuffer_ && indexBuffer_ && vertexCount && primCount);

	CHECKED_D3D_CALL(g_engine.videoImplD3D9->device().SetStreamSource(0, vertexBuffer_, 0, vertexSize_));
	CHECKED_D3D_CALL(g_engine.videoImplD3D9->device().SetIndices(indexBuffer_));
	CHECKED_D3D_CALL(g_engine.videoImplD3D9->device().DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, primCount));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECT3D9
