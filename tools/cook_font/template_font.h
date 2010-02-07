#ifndef ${font_name_up}_FONT_INCLUDED
#define ${font_name_up}_FONT_INCLUDED

//#include "video/font.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ${font_name}Font : public Font {
	static const uint MIN_GLYPH = ${min_glyph};
	static const uint MAX_GLYPH = ${max_glyph};
	static const uint GLYPH_COUNT = MAX_GLYPH - MIN_GLYPH + 1;

	static const uint MIN_KERN = ${min_kern};
	static const uint MAX_KERN = ${max_kern};
	static const uint KERN_COUNT = MAX_KERN - MIN_KERN + 1;

	static const uint MIN_KERN_MAP = ${min_kern_map};
	static const uint MAX_KERN_MAP = ${max_kern_map};
	static const uint KERN_MAP_COUNT = MAX_KERN_MAP - MIN_KERN_MAP + 1;

	static const Font::Glyph GLYPH_DATA[];
	static const i8 KERN_DATA[][KERN_MAP_COUNT];

	static const Font::Glyph* const GLYPHS[GLYPH_COUNT];
	static const i8* const KERNINGS[KERN_COUNT];

	static const Font::Info INFO;

public:
	${font_name}Font() : Font(INFO, GLYPHS, MIN_GLYPH, MAX_GLYPH, KERNINGS, MIN_KERN, MAX_KERN, MIN_KERN_MAP, MAX_KERN_MAP) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
