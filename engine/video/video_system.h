#ifndef VIDEO_SYSTEM_INCLUDED
#define VIDEO_SYSTEM_INCLUDED

#include "kaynine/utility/singleton.h"

#include "utility/holder.h"
#include "utility/safe_bool.h"
#include "utility/updatable.h"

namespace engine {

//=====================================================================================================================

class VideoSystem : 
	public Updatable, 
	public safe_bool<VideoSystem>, 
	public kaynine::Singleton<VideoSystem>
{
public:
	VideoSystem();
};

//=====================================================================================================================

#include "utility/holder.h"
typedef Holder<VideoSystem> Video;

}

#endif
