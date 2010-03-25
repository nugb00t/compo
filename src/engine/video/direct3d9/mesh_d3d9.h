#pragma once

#include "video/mesh.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DynamicMeshD3D9 : public DynamicMesh {
public:
    DynamicMeshD3D9(engine::Effect& effect, const uint vertexSize, const uint vertexCapacity, const uint indexCapacity);
    ~DynamicMeshD3D9();

    // interface: MeshImpl
    virtual void lock();
    virtual void unlock();

    virtual void streamBuffers(const uint vertexCount, const uint primCount);

private:
	// Direct3D
	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine
