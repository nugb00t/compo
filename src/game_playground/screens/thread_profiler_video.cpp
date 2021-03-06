#include "stdafx.h"

#include "thread_profiler_video.h"

#include "engine.h"
#include "core/time.h"

using namespace engine;
using namespace game_playground;

namespace {
	static const uint TIME_WINDOW_WIDTH	= 32;		// msec

	static const float SCREEN_LEFT		= -0.5f;
	static const float SCREEN_RIGHT		=  0.5f;
	static const float TIME_FRAME		=  (SCREEN_RIGHT - SCREEN_LEFT) / TIME_WINDOW_WIDTH;

	static const float SCREEN_TOP		=  0.5f;
	static const float SCREEN_BOTTOM	= -0.5f;

	static const float SCREEN_DEPTH		=  1.0f;

	static const float BAR_HEIGHT		=  0.1f;
	static const float BAR_OFFSET		=  0.15f;
	static const uint BAR_COLOR		=  0x88ffffff;
	//static const uint BAR_COLOR		=  0x80808080;

	static const uint MAX_VERTICES	= 1024;
	static const uint MAX_INDICES	= 1024;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ThreadProfilerVideo::initialize(engine::Video& video) {
	mesh_.reset(video.createDynamicMesh(sizeof(Vertex), MAX_VERTICES, MAX_INDICES));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ThreadProfilerVideo::draw(engine::Video& video, const Matrix44& view_projection) {
	mesh_->clear();
	{
		DynamicMesh::BufferAccess access(*mesh_);

		// top ruler
		{
			const float bottom	= SCREEN_TOP - BAR_HEIGHT;

			const short firstVertex = access.addVertex(Vertex(Vector3(SCREEN_LEFT, bottom, SCREEN_DEPTH), BAR_COLOR));
			access.addVertex(Vertex(Vector3(SCREEN_LEFT, SCREEN_TOP, SCREEN_DEPTH), BAR_COLOR));
			access.addVertex(Vertex(Vector3(SCREEN_RIGHT, SCREEN_TOP, SCREEN_DEPTH), BAR_COLOR));
			access.addVertex(Vertex(Vector3(SCREEN_RIGHT, bottom, SCREEN_DEPTH), BAR_COLOR));

			access.addIndex(firstVertex);
			access.addIndex(firstVertex + 1);
			access.addIndex(firstVertex + 2);
			access.addIndex(firstVertex + 2);
			access.addIndex(firstVertex + 3);
			access.addIndex(firstVertex);
		}

		const uint timeBegin = Profiler::inst().get(Profiler::VIDEO, -2).begin - 8;

		uint section;
		for (section = 0; section < Profiler::SECTION_COUNT; ++section) {
			for (int age = 0; age < Profiler::HISTORY_DEPTH; ++age) {
				const Profiler::Period& period = Profiler::inst().get((Profiler::Section)section, -age);

				const float left	= SCREEN_LEFT + ((float)period.begin - timeBegin - 0.5f) * TIME_FRAME;
				const float right	= SCREEN_LEFT + ((float)period.end   - timeBegin + 0.5f) * TIME_FRAME;

				const float top		= SCREEN_TOP - BAR_OFFSET * (section + 1);
				const float bottom	= top - BAR_HEIGHT;

				const uint color = Profiler::SECTION_COLORS[section];

				// fill-up vertex / index arrays
				const short firstVertex = access.addVertex(Vertex(Vector3(left, bottom, SCREEN_DEPTH), color));
				access.addVertex(Vertex(Vector3(left, top, SCREEN_DEPTH), color));
				access.addVertex(Vertex(Vector3(right, top, SCREEN_DEPTH), color));
				access.addVertex(Vertex(Vector3(right, bottom, SCREEN_DEPTH), color));

				access.addIndex(firstVertex);
				access.addIndex(firstVertex + 1);
				access.addIndex(firstVertex + 2);
				access.addIndex(firstVertex + 2);
				access.addIndex(firstVertex + 3);
				access.addIndex(firstVertex);
			}
		}

		// bottom ruler
		{
			const float top		= SCREEN_TOP - BAR_OFFSET * (section + 1);
			const float bottom	= top - BAR_HEIGHT;

			const short firstVertex = access.addVertex(Vertex(Vector3(SCREEN_LEFT, bottom, SCREEN_DEPTH), BAR_COLOR));
			access.addVertex(Vertex(Vector3(SCREEN_LEFT, top, SCREEN_DEPTH), BAR_COLOR));
			access.addVertex(Vertex(Vector3(SCREEN_RIGHT, top, SCREEN_DEPTH), BAR_COLOR));
			access.addVertex(Vertex(Vector3(SCREEN_RIGHT, bottom, SCREEN_DEPTH), BAR_COLOR));

			access.addIndex(firstVertex);
			access.addIndex(firstVertex + 1);
			access.addIndex(firstVertex + 2);
			access.addIndex(firstVertex + 2);
			access.addIndex(firstVertex + 3);
			access.addIndex(firstVertex);
		}
	}

	video.draw(*mesh_, Vertex::Type, EFFECT, 0, 0, view_projection);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
