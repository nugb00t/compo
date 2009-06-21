#include "stdafx.h"

#include "video/video_system.h"

#include "orb_video.h"

using namespace engine;
using namespace game;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OrbVideo::OrbVideo() 
: tex_(Video::get().createTexture()) {
	const unsigned v0 = mesh_.addVertice(Vertice(Vector3(-.5f, +.5f, -5.f), Vector3(0.f, 0.f, 1.f), Vector2(0.f, 0.f)));
	const unsigned v1 = mesh_.addVertice(Vertice(Vector3(+.5f, +.5f, -5.f), Vector3(0.f, 0.f, 1.f), Vector2(1.f, 0.f)));
	const unsigned v2 = mesh_.addVertice(Vertice(Vector3(+.5f, -.5f, -5.f), Vector3(0.f, 0.f, 1.f), Vector2(1.f, 1.f)));
	const unsigned v3 = mesh_.addVertice(Vertice(Vector3(-.5f, -.5f, -5.f), Vector3(0.f, 0.f, 1.f), Vector2(0.f, 1.f)));

	mesh_.addIndex(v0);
	mesh_.addIndex(v1);
	mesh_.addIndex(v2);

	mesh_.addIndex(v2);
	mesh_.addIndex(v3);
	mesh_.addIndex(v0);

	bool ok = tex_->load(_T("myself.bmp"));
	assert(ok);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool OrbVideo::update(const float UNUSED(dt)) {
	Video::get().draw(mesh_);

	tex_->update();

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

