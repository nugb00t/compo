#include "stdafx.h"

#include "orb_logic.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbLogic::decide(const ServerState& /*last*/, ServerRequests::Entity& request) {
	request.positionalVelocity.zero();

	request.rotationalVelocity.identity();
	cml::quaternion_rotation_euler(request.rotationalVelocity, 0.f, 0.f, 0.3f, cml::euler_order_xyz);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
