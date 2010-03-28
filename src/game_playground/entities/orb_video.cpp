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

const Effect::TextureUniform OrbVideo::TEX_UNIFORMS[] = {
    { "TEX_DIFFUSE", _T("playground/textures/myself.bmp") },
    Effect::TextureUniform::TERMINATOR
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbVideo::draw(engine::Video* const video, const ServerState::Entity& orb, const Matrix44& view_projection) {
	if (!mesh_ || !effect_) {
        assert(!mesh_ && !effect_);

		effect_.reset(video->createEffect(Vertex::type));
        effect_->setTexUniforms(TEX_UNIFORMS);

        mesh_.reset(video->createMesh(*effect_,
					sizeof(Vertex), 
					sizeof(vertices_) / sizeof(Vertex),
					sizeof(indices_) / sizeof(u16)));

        DynamicMesh::BufferAccess access(*mesh_);
		access.setBuffers(vertices_, sizeof(vertices_) / sizeof(Vertex), indices_, sizeof(indices_) / sizeof(u16));
	}

    Matrix44 transform;
	transform.identity();
	//cml::matrix_rotation_quaternion(transform, orb.rotation);
	cml::matrix_set_translation(transform, orb.position);

    transform *= view_projection;
	mesh_->draw(transform);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
