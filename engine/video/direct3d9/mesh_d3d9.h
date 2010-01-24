#ifndef MESH_D3D9_INCLUDED
#define MESH_D3D9_INCLUDED

#include "video/effect.h"

#include "video/mesh.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MeshD3D9 : public Mesh {
public:
	MeshD3D9(EffectPtr effect);
	~MeshD3D9();

	// interface: Drawn
	virtual void draw(const Matrix44& view_proj);

	// interface: Mesh
	virtual void setBuffers(const void* const vertices, const unsigned vertexCount, const unsigned vertexSize,
							const short* const indices, const unsigned indexCount);

private:
	// Direct3D
	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;

	unsigned vertexCount_;
	unsigned vertexSize_;
	unsigned verticesCapacity_;

	unsigned indexCount_;
	unsigned indicesCapacity_;

	engine::EffectPtr effect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif