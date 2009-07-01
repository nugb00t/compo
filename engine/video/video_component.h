#ifndef VIDEO_COMPONENT_INCLUDED
#define VIDEO_COMPONENT_INCLUDED

#include "utility/intrusive_ptr_base.h"
#include "utility/updatable.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoComponent : public Updatable {
public:
	typedef engine::VideoComponent Type;
};

typedef boost::intrusive_ptr<VideoComponent> VideoComponentPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
