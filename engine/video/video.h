#ifndef VIDEO_INCLUDED
#define VIDEO_INCLUDED

#include "server/server_data.h"

// factory-created objects
#include "camera.h"
#include "mesh.h"
#include "effect.h"
#include "texture.h"
#include "vertex_decl.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Video : public kaynine::PulseThreadObject {
	static const unsigned PERIOD = 16;
	static const unsigned DELAY = 4 * 10;

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
	virtual Mesh* createMesh(EffectPtr effect) = 0;
	virtual Effect* createEffect(const TCHAR* const path, const VertexDeclPtr vertexDecl) = 0;
	virtual Texture* createTexture(const TCHAR* const path) = 0;

	virtual VertexDeclPtr getVertexDecl(const VertexDecl::Type type) = 0;

	virtual Camera& camera() { assert(camera_); return *camera_; }

protected:
	boost::scoped_ptr<Camera> camera_;

	class VideoComponent* registry_[ServerState::MAX_ENTITIES];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
