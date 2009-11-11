#include "stdafx.h"

#include "orb_logic.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbLogic::update(ServerView::Entity& toVideo, const unsigned UNUSED(msec)) {
	const unsigned time = ::timeGetTime() % 1000;
	const float angle = time * (2.0f * D3DX_PI) / 1000.0f;

    // TODO: rotate this thing adding a const quaternion
	toVideo.direction.identity();
	cml::matrix_rotation_euler(toVideo.transform, angle, 0.f, 0.f, cml::euler_order_xyz);
	cml::matrix_set_translation(toVideo.transform, Vector3(0.f, 0.f, 5.f));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
