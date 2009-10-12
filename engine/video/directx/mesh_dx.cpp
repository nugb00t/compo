#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "mesh_dx.h"
#include "video_system_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshDX::MeshDX(EffectPtr effect)
: vertexBuffer_(NULL), indexBuffer_(NULL), 
  verticesSize_(0), verticesCapacity_(0), vertexSize_(0),
  indicesSize_(0), indicesCapacity_(0),
  effect_(effect) {
	assert(effect_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeshDX::~MeshDX() {
	if (vertexBuffer_)
		vertexBuffer_->Release();

	if (indexBuffer_)
		indexBuffer_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshDX::draw(const Matrix44& transform) {
	assert(effect_);
	assert(effect_);
	assert(effect_);

	CHECKED_D3D_CALL(VideoDX::inst().device().SetStreamSource(0, vertexBuffer_, 0, vertexSize_));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetIndices(indexBuffer_));

    effect_->setTransform(transform);
	effect_->begin();

	CHECKED_D3D_CALL(VideoDX::inst().device().DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, verticesSize_ / vertexSize_, 0, indicesSize_ / (3 * sizeof(short))));

	effect_->end();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshDX::setBuffers(const void* const vertices, const unsigned verticesSize, const unsigned vertexSize, 
						const short* const indices, const unsigned indicesSize) {
	assert(vertices);
	assert(indices);
	assert(verticesSize);
	assert(indicesSize);

	// vertex buffer
	if (vertexBuffer_ && verticesSize > verticesCapacity_)
		vertexBuffer_->Release();

	if (!vertexBuffer_) {
		CHECKED_D3D_CALL(VideoDX::inst().device().CreateVertexBuffer(verticesSize, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer_, NULL));
		verticesCapacity_ = verticesSize;
	}

	void* locked;
	CHECKED_D3D_CALL(vertexBuffer_->Lock(0, 0, &locked, D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD));
	::memcpy(locked, vertices, verticesSize);
	verticesSize_ = verticesSize;
	vertexSize_ = vertexSize;
	CHECKED_D3D_CALL(vertexBuffer_->Unlock());

	// index buffer
	if (indexBuffer_ && indicesSize > indicesCapacity_)
		indexBuffer_->Release();

	if (!indexBuffer_) {
		CHECKED_D3D_CALL(VideoDX::inst().device().CreateIndexBuffer(indicesSize, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer_, NULL));
		indicesCapacity_ = indicesSize;
	}

	CHECKED_D3D_CALL(indexBuffer_->Lock(0, 0, &locked, 0));
	::memcpy(locked, indices, indicesSize);
	indicesSize_ = indicesSize;
	CHECKED_D3D_CALL(indexBuffer_->Unlock());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECTX
