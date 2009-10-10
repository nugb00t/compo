#ifndef MESH_DX_INCLUDED
#define MESH_DX_INCLUDED

#include "video/effect.h"

#include "video/mesh.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MeshDX : public Mesh {
public:
	MeshDX(EffectPtr effect);
	~MeshDX();

	// interface: Drawn
	virtual void draw(const Matrix44& view_proj);

	// interface: Mesh
	virtual void setBuffers(const void* const vertices, const unsigned verticesSize, const unsigned vertexSize,
							const short* const indices, const unsigned indicesSize);

private:
	// Direct3D
	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;

	unsigned verticesCapacity_;
	unsigned verticesSize_;
	unsigned vertexSize_;

	unsigned indicesCapacity_;
	unsigned indicesSize_;

	engine::EffectPtr effect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif