#ifndef SLING_FONT_INCLUDED
#define SLING_FONT_INCLUDED

//#include "video/font.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SlingFont : public Font {
	static const uint MIN_GLYPH = 32;
	static const uint MAX_GLYPH = 183;
	static const uint GLYPH_COUNT = MAX_GLYPH - MIN_GLYPH;

	static const uint MIN_KERN = 34;
	static const uint MAX_KERN = 121;
	static const uint KERN_COUNT = MAX_KERN - MIN_KERN;

	static const uint MIN_KERN_MAP = 34;
	static const uint MAX_KERN_MAP = 122;
	static const uint KERN_MAP_COUNT = MAX_KERN - MIN_KERN;

	static const Font::Glyph GLYPH_DATA[];
	static const i8 KERN_DATA[][KERN_MAP_COUNT];

	static const Font::Glyph* const GLYPHS[GLYPH_COUNT];
	static const i8* const KERNINGS[KERN_COUNT];

	static const Font::Info INFO;

public:
	SlingFont() : Font(INFO, GLYPHS, MIN_GLYPH, MAX_GLYPH, KERNINGS, MIN_KERN, MAX_KERN, MIN_KERN_MAP, MAX_KERN_MAP) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
