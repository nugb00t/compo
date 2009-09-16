#include "stdafx.h"

#include "orb_logic.h"

using namespace engine;
using namespace game;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbLogic::update(Drawn::Params& toVideo, const float UNUSED(dt)) {
	const unsigned time = ::timeGetTime() % 1000;
	const float angle = time * (2.0f * D3DX_PI) / 1000.0f;

	toVideo.transform.identity();
	cml::matrix_rotation_euler(toVideo.transform, 0.f, 0.f, angle, cml::euler_order_xyz);
	cml::matrix_set_translation(toVideo.transform, Vector3(0.f, 0.f, 5.f));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
