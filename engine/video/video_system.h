#ifndef VIDEO_SYSTEM_INCLUDED
#define VIDEO_SYSTEM_INCLUDED

#include "utility/callable.h"
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

	// startup/shutdown
	virtual bool startup() = 0;
	virtual void shutdown() = 0;

	// object factory
	virtual CameraPtr createCamera() = 0;
	virtual MeshPtr createMesh() = 0;
	virtual TexturePtr createTexture() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<VideoSystem> Video;

}

#endif
