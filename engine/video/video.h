#ifndef VIDEO_INCLUDED
#define VIDEO_INCLUDED

#include "server/server_data.h"

// factory-created objects
#include "camera.h"
#include "mesh.h"
#include "effect.h"
#include "texture.h"
#include "vertex_decls.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Video : public kaynine::PulseThreadObject {
	static const uint PERIOD = 16;
	static const uint DELAY = 8 * 10;

public:
	Video();

public:
    // interface: kaynine::PulseThreadObject
    virtual bool update();
	virtual kaynine::Event& quit();
	virtual const uint period() const { return PERIOD; }	// *1 milliseconds
	virtual const uint delay() const { return DELAY; }		// *100 nanoseconds

public:
	// interface: own
	virtual void clear() = 0;
	virtual bool begin() = 0;
	virtual void end() = 0;
	virtual void present() = 0;

    // TEMP
	virtual ProjCamera* createProjCamera() = 0;
	virtual OrthoCamera* createOrthoCamera() = 0;
    // TEMP

	// object factory
	virtual DynamicMesh* createMesh(engine::Effect* effect, const uint vertexSize, const uint vertexCapacity, const uint indexCapacity) = 0;

	virtual Effect* createEffect(const VertexDecls::Type vertexDeclType) = 0;
	virtual Texture* createTexture(const TCHAR* const path) = 0;

	virtual void activateVertexDecl(const VertexDecls::Type type) = 0;

    // TEMP
	virtual ProjCamera& projCamera() { assert(projCamera_); return *projCamera_; }
	virtual OrthoCamera& orthoCamera() { assert(orthoCamera_); return *orthoCamera_; }
    // TEMP

protected:
    // TEMP
	boost::scoped_ptr<ProjCamera> projCamera_;
	boost::scoped_ptr<OrthoCamera> orthoCamera_;
    // TEMP

	class VideoComponent* registry_[ServerState::MAX_ENTITIES];
	class ScreenVideoComponent* screen_;

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
