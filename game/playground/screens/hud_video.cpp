#include "stdafx.h"

#include "hud_video.h"

#include "engine.h"

using namespace engine;
using namespace game_playground;

// TODO: move this to 'template_font.h'
const Effect::TextureUniform HUDVideo::TEX_UNIFORMS[] = {
	{ "TEX_DIFFUSE", _T("fonts/sling_16_o_0.dds") },
	Effect::TextureUniform::TERMINATOR
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HUDVideo::draw() {
	if (!effect_) {
		effect_ = g_engine.video->createEffect(Font::Vertex::type);
		effect_->setTexUniforms(TEX_UNIFORMS);
	}

	if (!mesh_)
		mesh_.reset(g_engine.video->createMesh(effect_, sizeof(Font::Vertex), MAX_VERTICES, MAX_INDICES));

	mesh_->clear();

	font_.print(*mesh_, L"Heya :)", Vector3(.1f, .1f, .1f), .05f, 0xff00ffff);

	mesh_->draw(g_engine.video->orthoCamera().view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
