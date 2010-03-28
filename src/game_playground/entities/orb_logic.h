#pragma once

#include "logic/logic_component.h"
#include "server/server_data.h"

#include <kaynine/utility/instance_count.h>

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbLogic : public engine::LogicComponent, public kaynine::InstanceCount<OrbLogic> {
public:
	typedef engine::LogicComponent Type;

public:
	// interface: LogicComponent
    virtual void decide(const engine::ServerState& last, engine::ServerRequests::Entity& request);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
