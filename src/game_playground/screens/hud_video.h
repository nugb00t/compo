#pragma once

#include "video/font.h"
#include "video/mesh.h"
#include "video/video.h"
#include "video/video_component.h"

#include "fonts/bureau_font.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class HUDVideo : public engine::ScreenVideoComponent {
	typedef engine::Video::PosDiffuseTex Vertex;

	static const uint MAX_VERTICES = 1024;
	static const uint MAX_INDICES = MAX_VERTICES / 4 * 6;

	// TODO: move this to 'template_font.h'
	//static const engine::Effect::TextureUniform FONT_TEX[2];

	static const engine::Video::EffectType  EFFECT = engine::Video::DIFFUSE_TEXTURED;

public:
	// interface: ScreenVideoComponent
	virtual void initialize(engine::Video& video);
	virtual void draw(engine::Video& video, const Matrix44& view_projection);

private:
	boost::scoped_ptr<engine::DynamicMesh> mesh_;
	engine::Video::TextureUniform texUniform_;
	
	game::BureauFont font_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
