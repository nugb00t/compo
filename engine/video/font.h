#pragma once

#include "video/vertex_decls.h"
#include "video/mesh.h"

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
	Font(const Info& info, const Glyph* const* glyphs, const uint glyphFirst, const uint glyphCount) 
		:	info_(info), glyphs_(glyphs), glyphFirst_(glyphFirst), glyphCount_(glyphCount) {}

	// interface: own
	virtual void print(DynamicMesh& mesh, const wchar_t* const string, const Vector3 pos, const float pixelSize, const u32 color) const;

	const Info& info() const { return info_; }

protected:
	inline const uint printChar(DynamicMesh::BufferAccess& access, const wchar_t chr, const Vector3 cursor, const float pixelSize, const u32 color) const;

protected:
	const Info& info_;

	const Glyph* const* glyphs_;
	const uint glyphFirst_, glyphCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class KernedFont : public Font {
public:
	KernedFont(const Info& info, const Glyph* const* glyphs, const uint glyphFirst, const uint glyphCount,
		const i8* const* kernings, const uint kernFirst, const uint kernCount, const uint kernMapFirst, const uint kernMapCount) 
		:	Font(info, glyphs, glyphFirst, glyphCount),
		kernings_(kernings), kernFirst_(kernFirst), kernCount_(kernCount), kernMapFirst_(kernMapFirst), kernMapCount_(kernMapCount)
	{}

	// interface: Font
	virtual void print(DynamicMesh& mesh, const wchar_t* const string, const Vector3 pos, const float pixelSize, const u32 color) const;

private:
	const i8* const* kernings_;
	const uint kernFirst_, kernCount_;
	const uint kernMapFirst_, kernMapCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const uint Font::printChar(class DynamicMesh::BufferAccess& access, const wchar_t chr, const Vector3 cursor, const float pixelSize, const u32 color) const {
	if (chr < glyphFirst_ || glyphCount_ <= chr) {
		assert(false);
		return 0;
	}

	const Glyph* const glyph = glyphs_[chr - glyphFirst_];
	if (!glyph) {
		assert(false);
		return 0;
	}

	// markup
	const Glyph::Markup& markup = glyph->markup;
	const float left	= cursor[0] + pixelSize * markup.x;
	const float right	= cursor[0] + pixelSize * (markup.x + markup.width);
	const float top		= cursor[1] - pixelSize * markup.y;
	const float bottom	= cursor[1] - pixelSize * (markup.y + markup.height);

	// fill-up vertex / index arrays
	const Glyph::TexCoords& tex = glyph->tex;
	const short firstVertex = access.appendVertex(Vertex(Vector3(left, bottom, cursor[2]), color, Vector2(tex.u0, tex.v1)));
	access.appendVertex(Vertex(Vector3(left, top, cursor[2]), color, Vector2(tex.u0, tex.v0)));
	access.appendVertex(Vertex(Vector3(right, top, cursor[2]), color, Vector2(tex.u1, tex.v0)));
	access.appendVertex(Vertex(Vector3(right, bottom, cursor[2]), color, Vector2(tex.u1, tex.v1)));

	access.appendIndex(firstVertex);
	access.appendIndex(firstVertex + 1);
	access.appendIndex(firstVertex + 2);
	access.appendIndex(firstVertex + 2);
	access.appendIndex(firstVertex + 3);
	access.appendIndex(firstVertex);
	
	return glyph->xAdvance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
