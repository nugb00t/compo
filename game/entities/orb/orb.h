#ifndef ORB_INCLUDED
#define ORB_INCLUDED

#include "entities/entity.h"

#include "orb_audio.h"
#include "orb_video.h"

namespace game {

//=====================================================================================================================

class Orb : public engine::Entity<OrbVideo, OrbAudio> {
public:
	virtual ~Orb() {}
};

//=====================================================================================================================

}

#endif
