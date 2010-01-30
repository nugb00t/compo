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
	static const unsigned PERIOD = 16;
	static const unsigned DELAY = 8 * 10;

public:
	Video();

public:
    // interface: kaynine::PulseThreadObject
    virtual bool update();
	virtual kaynine::Event& quit();
	virtual const unsigned period() const { return PERIOD; }	// *1 milliseconds
	virtual const unsigned delay() const { return DELAY; }		// *100 nanoseconds

public:
	// interface: own
	virtual void clear() = 0;
	virtual bool begin() = 0;
	virtual void end() = 0;
	virtual void present() = 0;

	// object factory
	virtual Camera* createCamera() = 0;

	virtual DynamicMesh* createMesh(engine::Effect* effect, const unsigned vertexSize, const unsigned vertexCapacity, const unsigned indexCapacity) = 0;

	virtual Effect* createEffect(const VertexDecls::Type vertexDeclType) = 0;
	virtual Texture* createTexture(const TCHAR* const path) = 0;

	virtual void activateVertexDecl(const VertexDecls::Type type) = 0;

	virtual Camera& camera() { assert(camera_); return *camera_; }

protected:
	boost::scoped_ptr<Camera> camera_;

	class VideoComponent* registry_[ServerState::MAX_ENTITIES];
	class ScreenVideoComponent* screen_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
