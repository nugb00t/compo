#ifndef MESH_D3D9_INCLUDED
#define MESH_D3D9_INCLUDED

#include "video/mesh.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DynamicMeshD3D9 : public DynamicMesh {
public:
    DynamicMeshD3D9(engine::Effect* const effect, const unsigned vertexSize, const unsigned vertexCapacity, const unsigned indexCapacity);
    ~DynamicMeshD3D9();

    // interface: MeshImpl
    virtual void lock();
    virtual void unlock();

    virtual void streamBuffers(const unsigned vertexCount, const unsigned primCount);

private:
	// Direct3D
	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif