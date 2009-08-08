#include "stdafx.h"

#include "video/video_system.h"

#include "orb_video.h"

using namespace engine;
using namespace game;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool OrbVideo::update(const float UNUSED(dt)) {
	if (!mesh_)
		mesh_ = Video::get().createMesh();
	else {
		unsigned time = ::timeGetTime() % 1000;
		float angle = time * (2.0f * D3DX_PI) / 1000.0f;
		::printf("angle: %f\n", angle);

		mesh_->draw(Vector3(0.f, 0.f, 0.f), Vector3(angle, 0.f, 0.f), Vector3(1.f, 1.f, 1.f));
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

