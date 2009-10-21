#include "stdafx.h"

#include "video/video_interface.h"

#include "orb_video.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const OrbVideo::Vertex OrbVideo::vertices_[] = {
	{ Vector3(-.5f, -.5f, 0.f), 0x0fff0000, Vector2(0.f, 1.f), Vector2(0.f, 0.f) },
	{ Vector3(-.5f,  .5f, 0.f), 0xff00ffff, Vector2(0.f, 0.f), Vector2(0.f, 0.f) },
	{ Vector3( .5f,  .5f, 0.f), 0x0f00ff00, Vector2(1.f, 0.f), Vector2(0.f, 0.f) },
	{ Vector3( .5f, -.5f, 0.f), 0xff00ffff, Vector2(1.f, 1.f), Vector2(0.f, 0.f) },
};

const short OrbVideo::indices_[] = {
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

OrbVideo::OrbVideo()
: mesh_(NULL), effect_(NULL) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrbVideo::update(const Entity::Params& fromLogic, const unsigned UNUSED(msec)) {
	if (!mesh_ || !effect_) {
        assert(!mesh_ && !effect_);

        effect_ = Video::inst().createEffect(_T("playground/fx/simple.h"), Video::inst().getVertexDecl(VertexDecl::POS_DIFFUSE_TEX));
        effect_->setUniforms(uniforms_);
        effect_->setTexUniforms(texUniforms_);

        mesh_ = Video::inst().createMesh(effect_);
		mesh_->setBuffers(vertices_, sizeof(vertices_), sizeof(Vertex), indices_, sizeof(indices_));
	}

    Matrix44 transform = fromLogic.transform;
    transform *= Video::inst().camera().view_projection();
	mesh_->draw(transform);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
