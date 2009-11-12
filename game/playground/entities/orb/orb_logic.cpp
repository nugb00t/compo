#include "stdafx.h"

#include "orb_logic.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbLogic::decide(const ServerState& /*last*/, ServerRequests::Entity& request) {
	const unsigned time = ::timeGetTime() % 1000;
	const float angle = time * (2.0f * D3DX_PI) / 1000.0f;

    // TODO: rotate this thing adding a const quaternion
    request.rotationalVelocity.identity();
	//cml::matrix_rotation_euler(request.rotationalVelocity, angle, 0.f, 0.f, cml::euler_order_xyz);
	//cml::matrix_set_translation(request.rotationalVelocity, Vector3(0.f, 0.f, 5.f));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
