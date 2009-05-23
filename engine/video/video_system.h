#ifndef VIDEO_SYSTEM_INCLUDED
#define VIDEO_SYSTEM_INCLUDED

#include "utility/callable.h"
#include "utility/updatable.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoSystem : public Callable, public Updatable {
public:
	VideoSystem();

	// interface: Callable
	virtual void operator()();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "utility/holder.h"
typedef engine::Holder<VideoSystem> Video;

}

#endif
