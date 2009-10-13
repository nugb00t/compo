#ifndef ORB_INCLUDED
#define ORB_INCLUDED

#include "utility/registrant.h"

#include "orb_logic.h"
#include "orb_video.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Orb : public engine::Registrant2<OrbLogic, OrbVideo> {};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif