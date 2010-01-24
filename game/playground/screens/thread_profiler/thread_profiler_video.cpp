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
	static VertexDecls::PosDiffuse vertices[MAX_VERTICES];
	static short indices[MAX_INDICES];

	memset(vertices, 0, sizeof(vertices));
	memset(indices, 0, sizeof(indices));

	if (!effect_)
		effect_ = g_engine.video->createEffect(_T("playground/fx/simple.h"), VertexDecls::POS_DIFFUSE_TEX);

	if (!mesh_)
		mesh_ = g_engine.video->createMesh(effect_);

	const unsigned timeWindowBegin	= g_engine.time->msec() / TIME_WINDOW_WIDTH - 1;	// the last full 0.1 sec tick

	short nextVertex = 0;
	unsigned nextIndex = 0;

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
			assert(nextIndex < MAX_INDICES - 6);
			indices[nextIndex++] = nextVertex;
			indices[nextIndex++] = nextVertex + 2;
			indices[nextIndex++] = nextVertex + 1;
			indices[nextIndex++] = nextVertex + 3;
			indices[nextIndex++] = nextVertex + 2;
			indices[nextIndex++] = nextVertex;

			assert(nextVertex < MAX_VERTICES - 4);
			vertices[nextVertex++] = VertexDecls::PosDiffuse(Vector3(left, bottom, SCREEN_DEPTH), BAR_COLOR);
			vertices[nextVertex++] = VertexDecls::PosDiffuse(Vector3(left, top, SCREEN_DEPTH), BAR_COLOR);
			vertices[nextVertex++] = VertexDecls::PosDiffuse(Vector3(right, top, SCREEN_DEPTH), BAR_COLOR);
			vertices[nextVertex++] = VertexDecls::PosDiffuse(Vector3(right, bottom, SCREEN_DEPTH), BAR_COLOR);
		}

	mesh_->setBuffers(vertices, nextVertex, sizeof(VertexDecls::PosDiffuse), indices, nextIndex);

	//Matrix44 transform = transformFromRect(SCREEN_LEFT, SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, SCREEN_DEPTH);
	//transform *= g_engine.video->camera().view_projection();
	//mesh_->draw(transform);

	mesh_->draw(g_engine.video->camera().view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

