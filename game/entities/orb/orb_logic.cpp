#include "stdafx.h"

#include "orb_logic.h"

using namespace engine;
using namespace game;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbLogic::update(Sync::EntityParams& toVideo, const float UNUSED(dt)) {
	unsigned time = ::timeGetTime() % 1000;
	float angle = time * (2.0f * D3DX_PI) / 1000.0f;

	toVideo.position = Vector3(0.f, 0.f, 0.f);
	toVideo.rotation = Vector3(0.f, 0.f, angle);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

