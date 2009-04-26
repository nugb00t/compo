#ifndef AUDIO_SYSTEM_INCLUDED
#define AUDIO_SYSTEM_INCLUDED

#include "audio_component.h"

namespace engine {

//=====================================================================================================================

class AudioSystem : public Updatable {
};

//=====================================================================================================================

#include "utility/holder.h"
typedef Holder<AudioSystem> Audio;

}

#endif
