#pragma once

// factory-created objects
#include "camera.h"
#include "mesh.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Video {
public:
	static const uint MAX_TEXTURES = 16;

	//-----------------------------------------------------------------------------------------------------------------

	enum VertexType {
		POS_DIFFUSE,
		POS_DIFFUSE_TEX,
		POS_TEX,
		//POS_NORMAL_TEX,

		VERTEX_DECL_COUNT
	};

#pragma pack(push, 4)
	struct PosDiffuse {
		static const VertexType Type = POS_DIFFUSE;

		Vector3 pos;
		uint diffuse;

		PosDiffuse() {}
		PosDiffuse(const Vector3 pos_, const uint diffuse_)
			: pos(pos_), diffuse(diffuse_) {}
	};

	struct PosDiffuseTex {
		static const VertexType Type = POS_DIFFUSE_TEX;

		Vector3 pos;
		uint diffuse;
		Vector2 tex;

		PosDiffuseTex() {}
		PosDiffuseTex(const Vector3 pos_, const uint diffuse_, const Vector2 tex_)
			: pos(pos_), diffuse(diffuse_), tex(tex_) {}
	};

	struct PosTex {
		static const VertexType Type = POS_TEX;

		Vector3 pos;
		float dummy;
		Vector2 tex;

		PosTex() {}
		PosTex(const Vector3 pos_, const Vector2 tex_) : pos(pos_), tex(tex_) {}
	};
#pragma pack(pop)

	//-----------------------------------------------------------------------------------------------------------------

	enum EffectType {
		DIFFUSE,
		DIFFUSE_TEXTURED,
		TEXTURED,

		EFFECT_COUNT
	};

	//-----------------------------------------------------------------------------------------------------------------
	
	struct TextureUniform {
		const TCHAR* path;
		const char* name;
		uint texture;	
	};

	//-----------------------------------------------------------------------------------------------------------------
	
public:
	// interface: own
	virtual bool initialize() = 0;
	virtual void terminate() = 0;
	
	virtual void begin() = 0;
	virtual void end() = 0;

	// assets
	virtual const uint addTexture(const TCHAR* const path) = 0;

	virtual void draw(Mesh& mesh, const VertexType vertexType, const EffectType effect,
					  const TextureUniform* const texUniforms, const uint textureCount,
					  //const void* const uniforms, const uint uniformCount,
					  const Matrix44& transform) = 0;

	// TEMP
	virtual ProjCamera* createProjCamera() = 0;
	virtual OrthoCamera* createOrthoCamera() = 0;
	// TEMP

	// object factory
	virtual StaticMesh* createStaticMesh(const uint vertexSize, const void* const vertices, const uint vertexCount, const u16* const indices, const uint indexCount) = 0;
	virtual DynamicMesh* createDynamicMesh(const uint vertexSize, const uint vertexCapacity, const uint indexCapacity) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
