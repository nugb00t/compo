#include "stdafx.h"

#include "video/video_system.h"

#include "orb_video.h"

using namespace engine;
using namespace game;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbVideo::update(const Sync::EntityParams& fromLogic, const float UNUSED(dt)) {
	if (!mesh_)
		mesh_ = Video::inst().createMesh();

	mesh_->setTransform(fromLogic.position, fromLogic.rotation, Vector3(1.f, 1.f, 1.f));
	mesh_->draw();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

