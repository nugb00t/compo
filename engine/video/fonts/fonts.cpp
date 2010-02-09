#include "stdafx.h"

#include "fonts.h"

#include "engine.h"

// baked fonts
#include "sling_font_data.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Font::print(DynamicMesh& mesh, const wchar_t* const string, const Vector3 pos, const float size, const u32 color) const {
	assert(string);

	DynamicMesh::BufferAccess access(mesh);

	const float scale = size / info_.lineHeight;
	float cursor = pos[0];

	for (uint i = 0; string[i]; ++i) {
		const wchar_t chr = string[i];
		if (chr < glyphFirst_ || glyphCount_ <= chr) {
			assert(false);
			continue;
		}

		const Glyph* const glyph = glyphs_[chr - glyphFirst_];
		if (!glyph) {
			assert(false);
			continue;
		}

		// markup
		const Glyph::Markup& markup = glyph->markup;
		const float left	= cursor + scale * markup.x;
		const float right	= cursor + scale * (markup.x + markup.width);
		const float top		= pos[1] - scale * markup.y;
		const float bottom	= pos[1] - scale * (markup.y + markup.height);

		// fill-up vertex / index arrays
		const Glyph::TexCoords& tex = glyph->tex;
		const short firstVertex = access.appendVertex(Vertex(Vector3(left, bottom, pos[2]), color, Vector2(tex.u0, tex.v1)));
		access.appendVertex(Vertex(Vector3(left, top, pos[2]), color, Vector2(tex.u0, tex.v0)));
		access.appendVertex(Vertex(Vector3(right, top, pos[2]), color, Vector2(tex.u1, tex.v0)));
		access.appendVertex(Vertex(Vector3(right, bottom, pos[2]), color, Vector2(tex.u1, tex.v1)));

		access.appendIndex(firstVertex);
		access.appendIndex(firstVertex + 1);
		access.appendIndex(firstVertex + 2);
		access.appendIndex(firstVertex + 2);
		access.appendIndex(firstVertex + 3);
		access.appendIndex(firstVertex);

		int advance = glyph->xAdvance;

		// kernings
		if (kernFirst_ <= chr && chr < kernCount_) {
			const i8* const kernMap = kernings_[chr - kernFirst_];
			const wchar_t chrNext = string[i + 1];

			if (kernMap && chrNext && kernMapFirst_ <= chrNext && chrNext < kernMapCount_)
				advance += kernMap[chrNext - kernMapFirst_];
		}

		cursor += scale * advance;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
