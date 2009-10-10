#include "stdafx.h"

#include "video/video_system.h"

#include "orb_video.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbVideo::update(const Drawn::Params& fromLogic, const float UNUSED(dt)) {
	if (!mesh_)
		mesh_ = Video::inst().createMesh(
			Video::inst().createEffect(_T("playground/fx/simple.h")), 
			Video::inst().createTexture(_T("playground/textures/myself.bmp")));

	mesh_->transform() = fromLogic.transform;
	mesh_->draw(Video::inst().camera().view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
