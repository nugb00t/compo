#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VertexDecls {
public:

    //-----------------------------------------------------------------------------------------------------------------

    enum Type {
		POS_DIFFUSE,
		POS_DIFFUSE_TEX,
		//POS_NORMAL_TEX,

		COUNT
	};

#pragma pack(push, 4)
	struct PosDiffuse {
        static const Type type = POS_DIFFUSE;

		Vector3 pos;
		uint diffuse;

		PosDiffuse() {}
		PosDiffuse(const Vector3 pos_, const uint diffuse_)
			: pos(pos_), diffuse(diffuse_) {}
	};

	struct PosDiffuseTex {
        static const Type type = POS_DIFFUSE_TEX;

		Vector3 pos;
		uint diffuse;
		Vector2 tex;

		PosDiffuseTex() {}
		PosDiffuseTex(const Vector3 pos_, const uint diffuse_, const Vector2 tex_)
			: pos(pos_), diffuse(diffuse_), tex(tex_) {}
	};
#pragma pack(pop)

    //-----------------------------------------------------------------------------------------------------------------

public:
	virtual void initialize() = 0;
	virtual void activate(const Type type) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
