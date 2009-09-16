#ifndef PROFILER_SCREEN_INCLUDED
#define PROFILER_SCREEN_INCLUDED

#include "profiler_screen_video.h"

namespace game {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ProfilerScreen : public engine::Registrant1<ProfilerScreenVideo> {};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
