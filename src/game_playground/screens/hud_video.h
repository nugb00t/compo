#pragma once

#include "video/video_component.h"

#include "video/font.h"
#include "video/mesh.h"

#include "fonts/bureau_font.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class HUDVideo : public engine::ScreenVideoComponent {
	static const uint MAX_VERTICES = 1024;
	static const uint MAX_INDICES = MAX_VERTICES / 4 * 6;

	// TODO: move this to 'template_font.h'
	static const engine::Effect::TextureUniform FONT_TEX[2];

public:
	// interface: VideoComponent
	virtual void draw(const Matrix44& view_projection);

private:
	boost::scoped_ptr<engine::Effect> effect_;
	boost::scoped_ptr<engine::DynamicMesh> mesh_;
	game::BureauFont font_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
