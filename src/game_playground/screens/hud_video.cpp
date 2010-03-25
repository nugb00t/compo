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

void HUDVideo::draw(const Matrix44& view_projection) {
	if (!effect_) {
		assert(!mesh_);
		effect_.reset(Engine::inst().videoImpl->createEffect(Font::Vertex::type));
		effect_->setTexUniforms(FONT_TEX);
		mesh_.reset(Engine::inst().videoImpl->createMesh(*effect_, sizeof(Font::Vertex), MAX_VERTICES, MAX_INDICES));
	}

	mesh_->clear();
	font_.print(*mesh_, L"Hula: Critical! ;)", Vector3(.1f, .05f, .1f), 1.f / 600.f, 0xffffffff);
	mesh_->draw(view_projection);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
