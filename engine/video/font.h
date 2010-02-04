#ifndef FONT_INCLUDED
#define FONT_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Font {
	static const uint GLYPH_COUNT = 4;	//256;

    //-----------------------------------------------------------------------------------------------------------------

    struct Glyph {
        uint x, y;
        uint width, height;
        uint xOffset, yOffset;
        uint xAdvance;
        uint page;

		Glyph(const uint x_, const uint y_, const uint width_, const uint height_,
			  const uint xOffset_, const uint yOffset_, const uint xAdvance_, const uint page_)
			  : x(x_), y(y_), width(width_), height(height_), 
			    xOffset(xOffset_), yOffset(yOffset_), xAdvance(xAdvance_), page(page_) 
		{}
    };

	static const Glyph* GLYPHS[GLYPH_COUNT];

    //-----------------------------------------------------------------------------------------------------------------

public:
	Font(const uint lineHeight, const uint base, 
		 const uint width, const uint height, const uint pages) 
	:	lineHeight_(lineHeight), base_(base), 
		width_(width), height_(height), pages_(pages)
	{
		memset(glyphs_, 0, sizeof(glyphs_));
		memset(kernings_, 0, sizeof(kernings_));
	}

protected:
	uint lineHeight_;
	uint base_;
	uint width_, height_;
	uint pages_;

	Glyph* glyphs_[GLYPH_COUNT];
	i8* kernings_[GLYPH_COUNT];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SlingFont : public Font {
public:
	SlingFont();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
