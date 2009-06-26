#ifndef MESH_DX_INCLUDED
#define MESH_DX_INCLUDED

#include "video/mesh.h"
#include "video/texture.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MeshDX : public Mesh {

#pragma pack(push, 4)
	struct Vertex {
		static const short FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		Vector3	point;
		unsigned color;
		//Vector3	normal;
		//Vector2	uv;

		//inline Vertex(const Vector3 point_ = Vector3(0.f, 0.f, 0.f), const Vector3 normal_ = Vector3(0.f, 0.f, 1.f), const Vector2 uv_ = Vector2(0.f, 0.f))
		//	: point(point_), normal(normal_), uv(uv_) {}
	};
#pragma pack(pop)

public:
	MeshDX();

	// interface: Updatable
	virtual bool update(const float dt);

private:
	static const Vertex vertices_[];
	IDirect3DVertexBuffer9* vb_;

	engine::TexturePtr texture_;

	D3DXMATRIX transform_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif