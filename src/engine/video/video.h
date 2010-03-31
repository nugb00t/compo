#pragma once

// factory-created objects
#include "camera.h"
#include "effect.h"
#include "mesh.h"
#include "texture.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Video {
public:

	//-----------------------------------------------------------------------------------------------------------------

	enum VertexDeclType {
		POS_DIFFUSE,
		POS_DIFFUSE_TEX,
		//POS_NORMAL_TEX,

		VERTEX_DECL_COUNT
	};

#pragma pack(push, 4)
	struct PosDiffuse {
		static const VertexDeclType Type = POS_DIFFUSE;

		Vector3 pos;
		uint diffuse;

		PosDiffuse() {}
		PosDiffuse(const Vector3 pos_, const uint diffuse_)
			: pos(pos_), diffuse(diffuse_) {}
	};

	struct PosDiffuseTex {
		static const VertexDeclType Type = POS_DIFFUSE_TEX;

		Vector3 pos;
		uint diffuse;
		Vector2 tex;

		PosDiffuseTex() {}
		PosDiffuseTex(const Vector3 pos_, const uint diffuse_, const Vector2 tex_)
			: pos(pos_), diffuse(diffuse_), tex(tex_) {}
	};
#pragma pack(pop)

	//-----------------------------------------------------------------------------------------------------------------

	enum EffectType {
		DIFFUSE,
		DIFFUSE_TEXTURED,

		EFFECT_COUNT
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	// interface: own
	virtual bool initialize() = 0;
	virtual void terminate() = 0;
	
	virtual void clear() = 0;
	virtual bool begin() = 0;
	virtual void end() = 0;
	virtual void present() = 0;

	// TEMP
	virtual ProjCamera* createProjCamera() = 0;
	virtual OrthoCamera* createOrthoCamera() = 0;
	// TEMP

	// object factory
	virtual DynamicMesh* createMesh(engine::Effect& effect, const uint vertexSize, const uint vertexCapacity, const uint indexCapacity) = 0;

	virtual Effect* createEffect(const EffectType type) = 0;
	virtual Texture* createTexture(const TCHAR* const path) = 0;

	virtual void activateVertexDecl(const VertexDeclType type) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
