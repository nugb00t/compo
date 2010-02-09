#ifndef HUD_VIDEO_INCLUDED
#define HUD_VIDEO_INCLUDED

#include "video/video_component.h"

#include "video/fonts/fonts.h"
#include "video/mesh.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class HUDVideo : public engine::ScreenVideoComponent {
	static const uint MAX_VERTICES = 1024;
	static const uint MAX_INDICES = MAX_VERTICES / 4 * 6;

	// TODO: move this to 'template_font.h'
	static const engine::Effect::TextureUniform TEX_UNIFORMS[];

public:
    HUDVideo() : effect_(NULL), mesh_(NULL) {}

	// interface: VideoComponent
	virtual void draw();

private:
	engine::Effect* effect_;
    boost::scoped_ptr<engine::DynamicMesh> mesh_;

	engine::SlingFont font_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
