#pragma once

// factory-created objects
#include "camera.h"
#include "mesh.h"
#include "effect.h"
#include "texture.h"
#include "vertex_decls.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoImpl {
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

	virtual Effect* createEffect(const VertexDecls::Type vertexDeclType) = 0;
	virtual Texture* createTexture(const TCHAR* const path) = 0;

	virtual void activateVertexDecl(const VertexDecls::Type type) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
