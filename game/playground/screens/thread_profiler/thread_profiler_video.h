#ifndef THREAD_PROFILER_VIDEO_INCLUDED
#define THREAD_PROFILER_VIDEO_INCLUDED

#include "core/profiler.h"
#include "video/video_component.h"

#include "video/effect.h"
#include "video/mesh.h"
#include "video/vertex_decls.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ThreadProfilerVideo : public engine::ScreenVideoComponent {
    typedef engine::VertexDecls::PosDiffuse Vertex;

public:
    ThreadProfilerVideo() : effect_(NULL), mesh_(NULL) {}

	// interface: VideoComponent
	virtual void draw();

private:
	void drawGrid();
	void drawDiagram();

private:
	engine::Effect* effect_;
    boost::scoped_ptr<engine::DynamicMesh> mesh_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
