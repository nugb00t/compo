#ifndef VIDEO_SYSTEM_INCLUDED
#define VIDEO_SYSTEM_INCLUDED

#include "utility/callable.h"
#include "utility/holder.h"

namespace engine {

class Mesh;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoSystem : 
	public Callable
{
public:
	VideoSystem();

	// interface: Callable
	virtual void operator()();

	// startup/shutdown
	virtual bool startup() = 0;
	virtual void shutdown() = 0;

	// utility
	virtual void clear() = 0;
	virtual bool init() = 0;
	virtual void flush() = 0;

	// image
	//virtual void tex2d(const int level, const int border, const Image& image) = 0;

	// viewport
	virtual void setOrthogonalView() = 0;
	//virtual void setPerspective(float fovY, float aspect, float zNear, float zFar) = 0;

	// drawing
	virtual void drawMesh(const Mesh& mesh) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<VideoSystem> Video;

}

#endif
