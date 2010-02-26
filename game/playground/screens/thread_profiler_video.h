#pragma once

#include "core/profiler.h"
#include "video/video_component.h"

#include "video/effect.h"
#include "video/mesh.h"
#include "video/vertex_decls.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ThreadProfilerVideo : public engine::ScreenVideoComponent {
    typedef engine::VertexDecls::PosDiffuse Vertex;
	static const uint MAX_VERTICES = (engine::Profiler::HISTORY_DEPTH * engine::Profiler::SECTION_COUNT + 2) * 4;
	static const uint MAX_INDICES = MAX_VERTICES / 4 * 6;

public:
    ThreadProfilerVideo() : effect_(NULL), mesh_(NULL) {}

	// interface: VideoComponent
	virtual void draw();

private:
	void drawGrid();
	void drawDiagram();

private:
	boost::scoped_ptr<engine::Effect> effect_;
    boost::scoped_ptr<engine::DynamicMesh> mesh_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
