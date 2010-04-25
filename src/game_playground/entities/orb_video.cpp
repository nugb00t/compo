#include "stdafx.h"

#include "engine.h"

#include "orb_video.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const OrbVideo::Vertex OrbVideo::vertices_[] = {
	Vertex(Vector3(-.5f, -.5f, 0.f), 0x0fff0000, Vector2(0.f, 1.f)),
	Vertex(Vector3(-.5f,  .5f, 0.f), 0xff00ffff, Vector2(0.f, 0.f)),
	Vertex(Vector3( .5f,  .5f, 0.f), 0x0f00ff00, Vector2(1.f, 0.f)),
	Vertex(Vector3( .5f, -.5f, 0.f), 0xff00ffff, Vector2(1.f, 1.f)),
};

const u16 OrbVideo::indices_[] = {
	0, 1, 2,
	2, 3, 0
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbVideo::initialize(engine::Video& video) {
	mesh_.reset(video.createStaticMesh(sizeof(Vertex), vertices_, sizeof(vertices_) / sizeof(Vertex), indices_, sizeof(indices_) / sizeof(u16)));

	texUniform_.path = _T("playground/textures/myself.bmp");
	texUniform_.name = "TEX_DIFFUSE";
	texUniform_.texture = video.addTexture(texUniform_.path);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbVideo::draw(engine::Video& video, const ServerState::Entity& orb, const Matrix44& view_projection) {
    Matrix44 transform;
	transform.identity();
	//cml::matrix_rotation_quaternion(transform, orb.rotation);
	cml::matrix_set_translation(transform, orb.position);

	// TODO: load up the texture
    transform *= view_projection;
	video.draw(*mesh_, Vertex::Type, EFFECT, &texUniform_, 1, transform);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
