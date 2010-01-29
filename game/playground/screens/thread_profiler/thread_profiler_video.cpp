#include "stdafx.h"

#include "thread_profiler_video.h"

#include "engine.h"
#include "core/time.h"

#include "video/vertex_decls.h"

using namespace engine;
using namespace game_playground;

namespace {
	static const unsigned TIME_WINDOW_WIDTH	= 96;		// msec

	static const float SCREEN_LEFT		= -0.5f;
	static const float SCREEN_RIGHT		=  0.5f;
	static const float SCREEN_TOP		=  0.5f;
	static const float SCREEN_BOTTOM	= -0.5f;
	static const float SCREEN_DEPTH		=  1.0f;

	static const float BAR_HEIGHT		=  0.1f;
	static const float BAR_OFFSET		=  0.15f;
	static const unsigned BAR_COLOR		=  0xffffffff;
	//static const unsigned BAR_COLOR		=  0x80808080;

	static const unsigned MAX_VERTICES	= 1024;
	static const unsigned MAX_INDICES	= 1024;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ThreadProfilerVideo::draw() {
	static Vertex vertices[MAX_VERTICES];
	static unsigned short indices[MAX_INDICES];

	memset(vertices, 0, sizeof(vertices));
	memset(indices, 0, sizeof(indices));

	if (!effect_)
		effect_ = g_engine.video->createEffect(_T("playground/fx/simple.h"), Vertex::type);

	if (!mesh_)
        mesh_.reset(g_engine.video->createMesh(effect_, 
                                               sizeof(Vertex), 
                                               Profiler::HISTORY_DEPTH * Profiler::SECTION_COUNT * 4,
                                               Profiler::HISTORY_DEPTH * Profiler::SECTION_COUNT * 6));

	const unsigned timeWindowBegin	= g_engine.time->msec() / TIME_WINDOW_WIDTH - 1;	// the last full 0.1 sec tick

	unsigned short vertexCount = 0;
	unsigned indexCount = 0;

	for (unsigned section = 0; section < Profiler::SECTION_COUNT; ++section)
		for (int age = 0; age < Profiler::HISTORY_DEPTH; ++age) {
			const Profiler::Period& period = g_engine.profiler->get((Profiler::Section)section, -age);

			if (!period.begin || !period.end)
				continue;

			const float left	= SCREEN_LEFT + (float)period.begin / TIME_WINDOW_WIDTH - timeWindowBegin;
			const float right	= SCREEN_LEFT + (float)period.end   / TIME_WINDOW_WIDTH - timeWindowBegin;

			const float top		= SCREEN_TOP - BAR_OFFSET * section;
			const float bottom	= top - BAR_HEIGHT;

			// fill-up vertex / index arrays
			assert(indexCount < MAX_INDICES - 6);
			indices[indexCount++] = vertexCount;
			indices[indexCount++] = vertexCount + 2;
			indices[indexCount++] = vertexCount + 1;
			indices[indexCount++] = vertexCount + 3;
			indices[indexCount++] = vertexCount + 2;
			indices[indexCount++] = vertexCount;

			assert(vertexCount < MAX_VERTICES - 4);
			vertices[vertexCount++] = Vertex(Vector3(left, bottom, SCREEN_DEPTH), BAR_COLOR);
			vertices[vertexCount++] = Vertex(Vector3(left, top, SCREEN_DEPTH), BAR_COLOR);
			vertices[vertexCount++] = Vertex(Vector3(right, top, SCREEN_DEPTH), BAR_COLOR);
			vertices[vertexCount++] = Vertex(Vector3(right, bottom, SCREEN_DEPTH), BAR_COLOR);
		}

    DynamicMesh::BufferAccess access(*mesh_);
    access.setBuffers(vertices, vertexCount, indices, indexCount);

	//Matrix44 transform = transformFromRect(SCREEN_LEFT, SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, SCREEN_DEPTH);
	//transform *= g_engine.video->camera().view_projection();
	//mesh_->draw(transform);

	mesh_->draw(g_engine.video->camera().view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

