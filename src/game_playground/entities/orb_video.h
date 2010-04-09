#pragma once

#include "video/video_component.h"
#include "video/video.h"
#include "video/effect.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbVideo : public engine::VideoComponent {
	typedef engine::Video::PosDiffuseTex Vertex;

	static const engine::Video::EffectType  EFFECT = engine::Video::DIFFUSE_TEXTURED;

public:
    OrbVideo() : mesh_(NULL), effect_(NULL) {}
	~OrbVideo() {}

	// interface: VideoComponent
	virtual void draw(engine::Video& video, const engine::ServerState::Entity& orb, const Matrix44& view_projection);

private:
	static const Vertex vertices_[];
	static const u16 indices_[];

    static const engine::Effect::TextureUniform TEX_UNIFORMS[];

    boost::scoped_ptr<engine::DynamicMesh> mesh_;
    boost::scoped_ptr<engine::Effect> effect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
