#ifndef VIDEO_SYSTEM_INCLUDED
#define VIDEO_SYSTEM_INCLUDED

#include "utility/holder.h"

// factory-created objects
#include "camera.h"
#include "mesh.h"
#include "texture.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoSystem : public Callable, public Updatable {
	static const unsigned FRAMERATE = 60;

public:
	VideoSystem();

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
	virtual MeshPtr createMesh() = 0;
	virtual TexturePtr createTexture() = 0;

private:
	CameraPtr camera_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<VideoSystem> Video;

}

#endif
