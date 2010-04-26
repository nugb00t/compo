#pragma once

#include "video/video.h"
#include "video/video_component.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbVideo : public engine::VideoComponent {
	typedef engine::Video::PosDiffuseTex Vertex;

	static const engine::Video::EffectType  EFFECT = engine::Video::DIFFUSE_TEXTURED;

public:
	// interface: VideoComponent
	virtual void initialize(engine::Video& video);
	virtual void draw(engine::Video& video, const engine::ServerState::Entity& orb, const Matrix44& view_projection);

private:
	static const Vertex vertices_[];
	static const u16 indices_[];

	boost::scoped_ptr<engine::StaticMesh> mesh_;
	engine::Video::TextureUniform texUniform_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
