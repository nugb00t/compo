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

const unsigned short OrbVideo::indices_[] = {
	//0, 1, 2,
	//2, 3, 0
	0, 2, 1,
	3, 2, 0
};

const Effect::Uniform OrbVideo::uniforms_[] = {
    Effect::Uniform::TERMINATOR
};

const Effect::TextureUniform OrbVideo::texUniforms_[] = {
    { "tex_diffuse", _T("playground/textures/myself.bmp") },
    Effect::TextureUniform::TERMINATOR
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbVideo::draw(const ServerState::Entity& fromClient) {
	if (!mesh_ || !effect_) {
        assert(!mesh_ && !effect_);

        effect_.reset(g_engine.video->createEffect(_T("playground/fx/simple.h"), Vertex::type));
        effect_->setUniforms(uniforms_);
        effect_->setTexUniforms(texUniforms_);

        mesh_.reset(g_engine.video->createMesh(effect_.get(), 
                                               sizeof(Vertex), 
                                               sizeof(vertices_) / sizeof(Vertex), 
                                               sizeof(indices_) / sizeof(unsigned short)));

        DynamicMesh::BufferAccess access(*mesh_);
		access.setBuffers(vertices_, sizeof(vertices_), indices_, sizeof(indices_));
	}

    Matrix44 transform;
	transform.identity();
	cml::matrix_rotation_quaternion(transform, fromClient.rotation);
	cml::matrix_set_translation(transform, fromClient.position);

    transform *= g_engine.video->camera().view_projection();
	mesh_->draw(transform);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
