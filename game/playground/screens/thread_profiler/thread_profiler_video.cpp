#include "stdafx.h"

#include "thread_profiler_video.h"

#include "engine.h"
#include "core/time.h"

#include "video/vertex_decls.h"

using namespace engine;
using namespace game_playground;

namespace {
	static const unsigned TIME_WINDOW_WIDTH	= 16;		// msec

	static const float SCREEN_LEFT		= -1.0f;
	static const float SCREEN_RIGHT		=  1.0f;
	static const float TIME_FRAME		=  (SCREEN_RIGHT - SCREEN_LEFT) / TIME_WINDOW_WIDTH;

	static const float SCREEN_TOP		=  1.0f;
	static const float SCREEN_BOTTOM	= -1.0f;

	static const float SCREEN_DEPTH		=  1.0f;

	static const float BAR_HEIGHT		=  0.1f;
	static const float BAR_OFFSET		=  0.15f;
	static const unsigned BAR_COLOR		=  0x88ffffff;
	//static const unsigned BAR_COLOR		=  0x80808080;

	static const unsigned MAX_VERTICES	= 1024;
	static const unsigned MAX_INDICES	= 1024;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ThreadProfilerVideo::draw() {
	if (!effect_)
		effect_ = g_engine.video->createEffect(Vertex::type);

	if (!mesh_)
		mesh_.reset(g_engine.video->createMesh(effect_, 
		sizeof(Vertex), 
		(Profiler::HISTORY_DEPTH * Profiler::SECTION_COUNT + 2) * 4,
		(Profiler::HISTORY_DEPTH * Profiler::SECTION_COUNT + 2) * 6));

	DynamicMesh::BufferAccess access(*mesh_);
	access.reset();

	// top ruler
	{
		const float bottom	= SCREEN_TOP - BAR_HEIGHT;

		const short firstVertex = access.appendVertex(Vertex(Vector3(SCREEN_LEFT, bottom, SCREEN_DEPTH), BAR_COLOR));
		access.appendVertex(Vertex(Vector3(SCREEN_LEFT, SCREEN_TOP, SCREEN_DEPTH), BAR_COLOR));
		access.appendVertex(Vertex(Vector3(SCREEN_RIGHT, SCREEN_TOP, SCREEN_DEPTH), BAR_COLOR));
		access.appendVertex(Vertex(Vector3(SCREEN_RIGHT, bottom, SCREEN_DEPTH), BAR_COLOR));

		access.appendIndex(firstVertex);
		access.appendIndex(firstVertex + 2);
		access.appendIndex(firstVertex + 1);
		access.appendIndex(firstVertex + 3);
		access.appendIndex(firstVertex + 2);
		access.appendIndex(firstVertex);
	}

	const unsigned timeBegin = g_engine.profiler->get(Profiler::VIDEO, -2).begin - 8;

	unsigned section;
	for (section = 0; section < Profiler::SECTION_COUNT; ++section) {
		for (int age = 0; age < Profiler::HISTORY_DEPTH; ++age) {
			const Profiler::Period& period = g_engine.profiler->get((Profiler::Section)section, -age);

			const float left	= SCREEN_LEFT + ((float)period.begin - timeBegin - 0.5f) * TIME_FRAME;
			const float right	= SCREEN_LEFT + ((float)period.end   - timeBegin + 0.5f) * TIME_FRAME;

			const float top		= SCREEN_TOP - BAR_OFFSET * (section + 1);
			const float bottom	= top - BAR_HEIGHT;

			const unsigned color = Profiler::SECTION_COLORS[section];

			// fill-up vertex / index arrays
			const short firstVertex = access.appendVertex(Vertex(Vector3(left, bottom, SCREEN_DEPTH), color));
			access.appendVertex(Vertex(Vector3(left, top, SCREEN_DEPTH), color));
			access.appendVertex(Vertex(Vector3(right, top, SCREEN_DEPTH), color));
			access.appendVertex(Vertex(Vector3(right, bottom, SCREEN_DEPTH), color));

			access.appendIndex(firstVertex);
			access.appendIndex(firstVertex + 2);
			access.appendIndex(firstVertex + 1);
			access.appendIndex(firstVertex + 3);
			access.appendIndex(firstVertex + 2);
			access.appendIndex(firstVertex);
		}
	}

	// bottom ruler
	{
		const float top		= SCREEN_TOP - BAR_OFFSET * (section + 1);
		const float bottom	= top - BAR_HEIGHT;

		const short firstVertex = access.appendVertex(Vertex(Vector3(SCREEN_LEFT, bottom, SCREEN_DEPTH), BAR_COLOR));
		access.appendVertex(Vertex(Vector3(SCREEN_LEFT, top, SCREEN_DEPTH), BAR_COLOR));
		access.appendVertex(Vertex(Vector3(SCREEN_RIGHT, top, SCREEN_DEPTH), BAR_COLOR));
		access.appendVertex(Vertex(Vector3(SCREEN_RIGHT, bottom, SCREEN_DEPTH), BAR_COLOR));

		access.appendIndex(firstVertex);
		access.appendIndex(firstVertex + 2);
		access.appendIndex(firstVertex + 1);
		access.appendIndex(firstVertex + 3);
		access.appendIndex(firstVertex + 2);
		access.appendIndex(firstVertex);
	}

	mesh_->draw(g_engine.video->camera().view_projection());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

