#ifndef ORB_AUDIO_INCLUDED
#define ORB_AUDIO_INCLUDED

#include "audio/audio_component.h"

namespace game {

//=====================================================================================================================

class OrbAudio : public engine::AudioComponent {
public:
	// interface: Updatable
	virtual void update(const float dt);
};

//=====================================================================================================================

}

#endif
