#pragma once

#include "../mesh.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StaticMeshD3D9 : public StaticMesh {
public:
	StaticMeshD3D9(const uint vertexSize, const uint vertexCount, const uint indexCount, const void* const vertices, const u16* const indices);

	virtual void streamBuffers(const uint vertexCount = 0, const uint primCount = 0);

private:
	// Direct3D
	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DynamicMeshD3D9 : public DynamicMesh {
public:
    DynamicMeshD3D9(const uint vertexSize, const uint vertexCapacity, const uint indexCapacity);
    ~DynamicMeshD3D9();

    virtual void lock();
    virtual void unlock();

    virtual void streamBuffers(const uint vertexCount = 0, const uint primCount = 0);

private:
	// Direct3D
	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine
