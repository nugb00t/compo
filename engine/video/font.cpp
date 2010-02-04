#include "stdafx.h"

#include "font.h"

using namespace engine;

const Font::Glyph* Font::GLYPHS[GLYPH_COUNT] = {
	NULL,
	NULL,
	new Glyph(65, 108, 10, 10, 0, 5, 11, 0),
	NULL
};

// <replacement regexps for RegexDesigner: http://www.radsoftware.com.au/?from=RegexDesigner :> 
//
// 
// 
//
// 
// 
//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
SlingFont::SlingFont() : Font(20, 15, 128, 128, 1) {
	glyphs_[32] = new Glyph(126, 0, 1, 1, 0, 15, 5, 0);
	glyphs_[33] = new Glyph(122, 17, 5, 13, 1, 2, 8, 0);
}
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
