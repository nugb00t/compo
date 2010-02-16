#include "stdafx.h"

#include "hud_video.h"

#include "engine.h"

using namespace engine;
using namespace game_playground;

const Effect::TextureUniform HUDVideo::FONT_TEX[2] = {
	{ "TEX_DIFFUSE", _T("fonts/bureau_20_o_0.dds") },
	Effect::TextureUniform::TERMINATOR
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HUDVideo::draw() {
	if (!effect_) {
		assert(!mesh_);
		effect_.reset(g_engine.video->createEffect(Font::Vertex::type));
		effect_->setTexUniforms(FONT_TEX);
		mesh_.reset(g_engine.video->createMesh(*effect_, sizeof(Font::Vertex), MAX_VERTICES, MAX_INDICES));
	}

	mesh_->clear();
	font_.print(*mesh_, L"Hula: Critical! ;)", Vector3(.1f, .05f, .1f), 1.f / 600.f, 0xffffffff);
	mesh_->draw(g_engine.video->orthoCamera().view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
