#ifndef FONT_INCLUDED
#define FONT_INCLUDED

#include "video/vertex_decls.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Font {
public:
	typedef engine::VertexDecls::PosDiffuseTex Vertex;

	//-----------------------------------------------------------------------------------------------------------------

#pragma pack(push, 4)
    struct Glyph {
		struct TexCoords {
			float u0, v0;
			float u1, v1;
		} tex;
#pragma pack(push, 2)
		struct Markup {
			i16 x, y;
			u16 width, height;
		} markup;
#pragma pack(pop)
		int xAdvance;
		uint page;
    };
#pragma pack(pop)

	//-----------------------------------------------------------------------------------------------------------------

	struct Info {
		uint lineHeight;
		uint base;
		uint width, height;
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	Font(const Info& info, 
		const Glyph* const* glyphs, const uint glyphFirst, const uint glyphCount,
		const i8* const* kernings, const uint kernFirst, const uint kernCount, const uint kernMapFirst, const uint kernMapCount) 
		:	info_(info), 
			glyphs_(glyphs), glyphFirst_(glyphFirst), glyphCount_(glyphCount),
			kernings_(kernings), kernFirst_(kernFirst), kernCount_(kernCount), kernMapFirst_(kernMapFirst), kernMapCount_(kernMapCount)
	{}

	void print(class DynamicMesh& mesh, const wchar_t* const string, const Vector3 pos, const float size, const u32 color) const;

private:
	const Info& info_;

	const Glyph* const* glyphs_;
	const uint glyphFirst_, glyphCount_;

	const i8* const* kernings_;
	const uint kernFirst_, kernCount_;
	const uint kernMapFirst_, kernMapCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#include "sling_font.h"

#endif
