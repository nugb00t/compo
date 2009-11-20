#ifndef VIDEO_INTERFACE_INCLUDED
#define VIDEO_INTERFACE_INCLUDED

// factory-created objects
#include "camera.h"
#include "mesh.h"
#include "effect.h"
#include "texture.h"
#include "vertex_decl.h"

#include "video_component.h"

namespace engine {

typedef kaynine::Holder<class VideoInterface> Video;
typedef boost::intrusive_ptr<class VideoInterface> VideoPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoInterface : public kaynine::IntrusivePtrBase {
public:
    VideoInterface::VideoInterface() { Video::set(*this); }

    // kaynine::thread meta-interface
    bool initialize();
    bool update();
    void terminate() { Video::inst().shutdown(); }

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
    VideoComponentRegistry registry_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
