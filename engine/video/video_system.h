#ifndef VIDEO_SYSTEM_INCLUDED
#define VIDEO_SYSTEM_INCLUDED

namespace engine {

//=====================================================================================================================

class VideoSystem : public Updatable {
};

//=====================================================================================================================

#include "utility/holder.h"
typedef Holder<VideoSystem> Video;

}

#endif
