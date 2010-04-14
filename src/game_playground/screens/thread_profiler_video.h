#pragma once

#include "utility/profiler.h"
#include "video/video_component.h"

#include "video/video.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ThreadProfilerVideo : public engine::ScreenVideoComponent {
    typedef engine::Video::PosDiffuse Vertex;

	static const uint MAX_VERTICES = (engine::Profiler::HISTORY_DEPTH * engine::Profiler::SECTION_COUNT + 2) * 4;
	static const uint MAX_INDICES = MAX_VERTICES / 4 * 6;

	static const engine::Video::EffectType  EFFECT = engine::Video::DIFFUSE;

public:
	// interface: VideoComponent
	virtual void draw(engine::Video& video, const Matrix44& view_projection);

private:
	void drawGrid();
	void drawDiagram();

private:
    boost::scoped_ptr<engine::DynamicMesh> mesh_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
