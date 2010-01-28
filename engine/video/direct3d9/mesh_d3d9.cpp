#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "mesh_d3d9.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshD3D9::MeshD3D9(EffectPtr effect, const unsigned vertexSize, 
                   const unsigned vertexCapacity, const unsigned indexCapacity)
:   effect_(effect), vertexSize_(vertexSize),
    vertexCapacity_(vertexCapacity), indexCapacity_(indexCapacity),
    vertexCount_(0), indexCount_(0), 
    vertexBuffer_(NULL), indexBuffer_(NULL), 
{
	assert(effect_ && vertexSize && vertexCapacity && indexCapacity);

    CHECKED_D3D_CALL(g_engine.videoD3D9->device().CreateVertexBuffer(vertexSize_ * vertexCapacity_, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));
    CHECKED_D3D_CALL(g_engine.videoD3D9->device().CreateIndexBuffer(sizeof(short) * indexCapacity_, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshD3D9::~MeshD3D9() {
	if (vertexBuffer_)
		vertexBuffer_->Release();

	if (indexBuffer_)
		indexBuffer_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshD3D9::draw(const Matrix44& transform) {
	assert(vertexBuffer_ && indexBuffer_ && verticesCapacity_ && indicesCapacity_ && effect_);

	CHECKED_D3D_CALL(g_engine.videoD3D9->device().SetStreamSource(0, vertexBuffer_, 0, vertexSize_));
	CHECKED_D3D_CALL(g_engine.videoD3D9->device().SetIndices(indexBuffer_));

    effect_->setTransform(transform);
	effect_->begin();

	CHECKED_D3D_CALL(g_engine.videoD3D9->device().DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount_, 0, indexCount_ / 3));

	effect_->end();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshD3D9::load(const void* const vertices, const unsigned vertexCount, 
					const short* const indices, const unsigned indexCount) {
	assert(vertexBuffer_ && indexBuffer_ && vertices && indices && vertexCount && indexCount);
    assert(vertexCount <= vertexCapacity_ && indexCount <= indexCapacity_);

	vertexCount_ = vertexCount;
    indexCount_ = indexCount;

	void* locked;
	CHECKED_D3D_CALL(vertexBuffer_->Lock(0, 0, &locked, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
	::memcpy(locked, vertices, vertexSize_ * vertexCount);
	CHECKED_D3D_CALL(vertexBuffer_->Unlock());

	CHECKED_D3D_CALL(indexBuffer_->Lock(0, 0, &locked, 0));
	::memcpy(locked, indices, sizeof(short) * indexCount);
	CHECKED_D3D_CALL(indexBuffer_->Unlock());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECT3D9
