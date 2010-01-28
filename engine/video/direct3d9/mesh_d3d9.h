#ifndef MESH_D3D9_INCLUDED
#define MESH_D3D9_INCLUDED

#include "video/effect.h"

#include "video/mesh.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MeshD3D9 : public Mesh {
public:
	MeshD3D9(EffectPtr effect, const unsigned vertexSize, 
             const unsigned maxVertexCount, const unsigned maxIndexCount);
	virtual ~MeshD3D9();

	// interface: Drawn
	virtual void draw(const Matrix44& view_proj);

	// interface: Mesh
    virtual void load(const void* const vertices, const unsigned vertexCount, 
                      const short* const indices, const unsigned indexCount);

private:
    const engine::Effect* effect_;
    const unsigned vertexSize_;
    const unsigned vertexCapacity_;
    const unsigned indexCapacity_;

	unsigned vertexCount_;
	unsigned indexCount_;

	// Direct3D
	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif