#ifndef ORB_LOGIC_INCLUDED
#define ORB_LOGIC_INCLUDED

#include "logic/logic_component.h"
#include "server/server_data.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbLogic : public engine::LogicComponent {
public:
	typedef engine::LogicComponent Type;

public:
	// interface: LogicComponent
    virtual void decide(const engine::ServerState& last, engine::ServerRequests::Entity& request);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
