#ifndef ORB_LOGIC_INCLUDED
#define ORB_LOGIC_INCLUDED

#include "logic/logic_component.h"

namespace game {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbLogic : public engine::LogicComponent {
public:
	typedef engine::LogicComponent Type;

public:
	// interface: LogicComponent
	virtual void update(engine::Sync::EntityParams& toVideo, const float dt);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
