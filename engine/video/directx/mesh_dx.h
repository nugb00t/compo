#ifndef MESH_DX_INCLUDED
#define MESH_DX_INCLUDED

#include "video/mesh.h"
#include "video/texture.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MeshDX : public Mesh {

#pragma pack(push, 4)
	struct Vertex {
		static const D3DVERTEXELEMENT9 Elements[];

		Vector3	xyz;
		unsigned diffuse;
		//Vector3	normal;
		Vector2	uv;

		//inline Vertex(const Vector3 point_ = Vector3(0.f, 0.f, 0.f), const Vector3 normal_ = Vector3(0.f, 0.f, 1.f), const Vector2 uv_ = Vector2(0.f, 0.f))
		//	: point(point_), normal(normal_), uv(uv_) {}
	};
#pragma pack(pop)

public:
	MeshDX();
	~MeshDX();

	// interface: Drawn
	virtual void draw();

private:
	static const Vertex vertices_[];
	static const short indices_[];

	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;
	IDirect3DVertexDeclaration9* vertexDecl_;

	engine::TexturePtr texture_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif