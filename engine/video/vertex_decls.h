#ifndef VERTEX_DECLS_INCLUDED
#define VERTEX_DECLS_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VertexDecls {
public:
	enum Type {
		POS_DIFFUSE,
		POS_DIFFUSE_TEX,
		//POS_NORMAL_TEX,

		COUNT
	};

	struct PosDiffuse {
		Vector3 pos;
		unsigned diffuse;

		PosDiffuse() {}
		PosDiffuse(const Vector3 pos_, const unsigned diffuse_)
			: pos(pos_), diffuse(diffuse_) {}
	};

	struct PosDiffuseTex {
		Vector3 pos;
		unsigned diffuse;
		Vector2 tex;

		PosDiffuseTex() {}
		PosDiffuseTex(const Vector3 pos_, const unsigned diffuse_, const Vector2 tex_)
			: pos(pos_), diffuse(diffuse_), tex(tex_) {}
	};

public:
	virtual void initialize() = 0;
	virtual void activate(const Type type) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
