#include "stdafx.h"

#include "video/video_system.h"

#include "orb_video.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const OrbVideo::Vertex OrbVideo::vertices_[] = {
	{ Vector3(-.5f, -.5f, 0.f), 0x0fff0000, Vector2(0.f, 1.f) },
	{ Vector3(-.5f,  .5f, 0.f), 0xff00ffff, Vector2(0.f, 0.f) },
	{ Vector3( .5f,  .5f, 0.f), 0x0f00ff00, Vector2(1.f, 0.f) },
	{ Vector3( .5f, -.5f, 0.f), 0xff00ffff, Vector2(1.f, 1.f) },
};

const short OrbVideo::indices_[] = {
	//0, 1, 2,
	//2, 3, 0
	0, 2, 1,
	3, 2, 0
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbVideo::update(const Drawn::Params& fromLogic, const float UNUSED(dt)) {
	if (!mesh_) {

		mesh_ = Video::inst().createMesh(
			Video::inst().createEffect(
				_T("playground/fx/simple.h"),
				Video::inst().getVertexDecl(VertexDecl::POS_DIFFUSE_TEX),
				Video::inst().createTexture(_T("playground/textures/myself.bmp"))
			));

		mesh_->setBuffers(vertices_, sizeof(vertices_), sizeof(Vertex), indices_, sizeof(indices_));
	}

	mesh_->transform() = fromLogic.transform;
	mesh_->draw(Video::inst().camera().view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
