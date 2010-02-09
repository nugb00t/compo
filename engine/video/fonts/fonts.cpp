#include "stdafx.h"

#include "fonts.h"

#include "engine.h"

// baked fonts
#include "sling_font_data.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Font::print(DynamicMesh& mesh, const wchar_t* const string, const Vector3 pos, const float scale, const u32 color) const {
	assert(string);

	// info_.lineHeight;

	DynamicMesh::BufferAccess access(mesh);

	for (uint i = 0; string[i]; ++i) {
		assert(string[i] < maxGlyph_);

		const Glyph* const glyph = glyphs_[string[i] - minGlyph_];
		assert(glyph);

		// fill-up vertex / index arrays
		const short firstVertex = access.appendVertex(Vertex(Vector3(left, bottom, pos[2]), color, Vector2(glyph->u0, glyph->v0)));
		access.appendVertex(Vertex(Vector3(left, top, pos[2]), color, Vector2(glyph->u0, glyph->v1)));
		access.appendVertex(Vertex(Vector3(right, top, pos[2]), color, Vector2(glyph->u1, glyph->v1)));
		access.appendVertex(Vertex(Vector3(right, bottom, pos[2]), color, Vector2(glyph->u1, glyph->v0)));

		access.appendIndex(firstVertex);
		access.appendIndex(firstVertex + 1);
		access.appendIndex(firstVertex + 2);
		access.appendIndex(firstVertex + 2);
		access.appendIndex(firstVertex + 3);
		access.appendIndex(firstVertex);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
