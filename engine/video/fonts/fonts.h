#ifndef FONT_INCLUDED
#define FONT_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Font {
public:

#pragma pack(push, 4)
    struct Glyph {
        float u0, v0, u1, v1;
        int xOffset, yOffset;
        int xAdvance;
		uint page;
    };
#pragma pack(pop)

	struct Info {
		uint lineHeight;
		uint base;
		uint width;
		uint height;
	};

public:
	Font(const Info& info, 
		const Glyph* const* glyphs, const uint minGlyph, const uint maxGlyph,
		const i8* const* kernings, const uint minKern, const uint maxKern, const uint minKernMap, const uint maxKernMap) 
		:	info_(info), 
			glyphs_(glyphs), minGlyph_(minGlyph), maxGlyph_(maxGlyph),
			kernings_(kernings), minKern_(minKern), maxKern_(maxKern), minKernMap_(minKernMap), maxKernMap_(maxKernMap) {}

private:
	const Info& info_;

	const Glyph* const* glyphs_;
	const uint minGlyph_;
	const uint maxGlyph_;

	const i8* const* kernings_;
	const uint minKern_;
	const uint maxKern_;
	const uint minKernMap_;
	const uint maxKernMap_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#include "sling_font.h"

#endif
