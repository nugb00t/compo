#ifndef VIDEO_INTERFACE_INCLUDED
#define VIDEO_INTERFACE_INCLUDED

// factory-created objects
#include "camera.h"
#include "mesh.h"
#include "effect.h"
#include "texture.h"
#include "vertex_decl.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoInterface : public Callable, public Updatable, public IntrusivePtrBase {
	static const unsigned FRAMERATE = 60;

public:
	VideoInterface();

	// interface: Callable
	virtual void operator()();

	// interface: Updatable
	virtual void update(const float dt);

	// startup / shutdown
	virtual bool startup() = 0;
	virtual void shutdown() = 0;

	// frame
	virtual void clear() = 0;
	virtual bool begin() = 0;
	virtual void end() = 0;
	virtual void present() = 0;

	// object factory
	virtual CameraPtr createCamera() = 0;
	virtual MeshPtr createMesh(EffectPtr effect) = 0;
	virtual EffectPtr createEffect(const TCHAR* const path, const VertexDeclPtr vertexDecl) = 0;
	virtual TexturePtr createTexture(const TCHAR* const path) = 0;

	virtual VertexDeclPtr getVertexDecl(const VertexDecl::Type type) = 0;

	// HACK (?)
	virtual const Camera& camera() const { return *camera_; }

private:
	CameraPtr camera_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<VideoInterface> Video;
typedef boost::intrusive_ptr<VideoInterface> VideoPtr;

}

#endif
