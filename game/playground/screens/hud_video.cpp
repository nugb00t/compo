#include "stdafx.h"

#include "hud_video.h"

#include "engine.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HUDVideo::draw() {
	if (!effect_)
		effect_ = g_engine.video->createEffect(Font::Vertex::type);

	if (!mesh_)
		mesh_.reset(g_engine.video->createMesh(effect_, sizeof(Font::Vertex), MAX_VERTICES, MAX_INDICES));

	mesh_->clear();

	font_.print(*mesh_, L"Heya :)", Vector3(.1f, .1f, .1f), .1f, 0x0800ffff);

	mesh_->draw(g_engine.video->orthoCamera().view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
