#include "stdafx.h"

#include "fonts.h"

#include "engine.h"

// baked fonts
#include "sling_font_data.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Font::print(DynamicMesh* mesh, const char* const string, const float x, const float y, const float scale) const {
	assert(mesh && string);

	DynamicMesh::BufferAccess access(*mesh);

	//// fill-up vertex / index arrays
	//const short firstVertex = access.appendVertex(Vertex(Vector3(left, bottom, SCREEN_DEPTH), color));
	//access.appendVertex(Vertex(Vector3(left, top, SCREEN_DEPTH), color));
	//access.appendVertex(Vertex(Vector3(right, top, SCREEN_DEPTH), color));
	//access.appendVertex(Vertex(Vector3(right, bottom, SCREEN_DEPTH), color));

	//access.appendIndex(firstVertex);
	//access.appendIndex(firstVertex + 1);
	//access.appendIndex(firstVertex + 2);
	//access.appendIndex(firstVertex + 2);
	//access.appendIndex(firstVertex + 3);
	//access.appendIndex(firstVertex);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
