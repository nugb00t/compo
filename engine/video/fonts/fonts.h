#ifndef FONT_INCLUDED
#define FONT_INCLUDED

#include "video/vertex_decls.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Font {
public:
	typedef engine::VertexDecls::PosDiffuseTex Vertex;

public:

	//-----------------------------------------------------------------------------------------------------------------

#pragma pack(push, 4)
    struct Glyph {
		struct source {
			float u0, v0, u1, v1;
		};
#pragma pack(push, 2)
		struct destination {
			i16 x0, y0;
			u16 width, height;
		};
#pragma pack(pop)
		source src;
		destination dest;
		int xAdvance, page;
    };
#pragma pack(pop)

	//-----------------------------------------------------------------------------------------------------------------

	struct Info {
		uint lineHeight, base, width, height;
	};

public:
	Font(const Info& info, 
		const Glyph* const* glyphs, const uint minGlyph, const uint maxGlyph,
		const i8* const* kernings, const uint minKern, const uint maxKern, const uint minKernMap, const uint maxKernMap) 
		:	info_(info), 
			glyphs_(glyphs), minGlyph_(minGlyph), maxGlyph_(maxGlyph),
			kernings_(kernings), minKern_(minKern), maxKern_(maxKern), minKernMap_(minKernMap), maxKernMap_(maxKernMap)
	{}

	void print(class DynamicMesh& mesh, const wchar_t* const string, const Vector3 pos, const float scale, const u32 color) const;

private:
	const Info& info_;

	const Glyph* const* glyphs_;
	const uint minGlyph_, maxGlyph_;

	const i8* const* kernings_;
	const uint minKern_, maxKern_;
	const uint minKernMap_, maxKernMap_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#include "sling_font.h"

#endif
