#include "stdafx.h"

#include "hud_video.h"

#include "engine.h"

using namespace engine;
using namespace game_playground;

//const Effect::TextureUniform HUDVideo::FONT_TEX[2] = {
//	{ "TEX_DIFFUSE", _T("main/fonts/bureau_20_o_0.dds") },
//	Effect::TextureUniform::TERMINATOR
//};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HUDVideo::draw(engine::Video& video, const Matrix44& view_projection) {
	if (!mesh_)
		mesh_.reset(video.createMesh(sizeof(Font::Vertex), MAX_VERTICES, MAX_INDICES));

	mesh_->clear();
	font_.print(*mesh_, L"Hula: Critical! ;)", Vector3(.1f, .05f, .1f), 1.f / 600.f, 0xffffffff);

	video.draw(*mesh_, Vertex::Type, EFFECT, /**/0, 0, view_projection);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
