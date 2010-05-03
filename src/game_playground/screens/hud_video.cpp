#include "stdafx.h"

#include "hud_video.h"

#include "engine.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HUDVideo::initialize(engine::Video& video) {
	mesh_.reset(video.createDynamicMesh(sizeof(Font::Vertex), MAX_VERTICES, MAX_INDICES));
	
	texUniform_.path = _T("main\\fonts\\bureau_20_o_0.dds");
	texUniform_.name = "TEX_DIFFUSE";
	texUniform_.texture = video.addTexture(texUniform_.path);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HUDVideo::draw(engine::Video& video, const Matrix44& view_projection) {
	mesh_->clear();
	font_.print(*mesh_, L"Hula: Critical! ;)", Vector3(.1f, .05f, .1f), 1.f / 600.f, 0xffffffff);

	video.draw(*mesh_, Vertex::Type, EFFECT, &texUniform_, 1, view_projection);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
