#include "stdafx.h"

#include "font.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Font::print(DynamicMesh& mesh, const wchar_t* const string, const Vector3 pos, const float pixelSize, const u32 color) const {
	assert(string);

	DynamicMesh::BufferAccess access(mesh);

	const float correction = pixelSize / 2.f;
	Vector3 cursor = pos - Vector3(correction, correction, 0.f);

	for (uint i = 0; string[i]; ++i) {
		const uint advance = printChar(access, string[i], cursor, pixelSize, color);
		
		cursor += Vector3(pixelSize * advance, 0.f, 0.f);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KernedFont::print(DynamicMesh& mesh, const wchar_t* const string, const Vector3 pos, const float pixelSize, const u32 color) const {
	assert(string);

	DynamicMesh::BufferAccess access(mesh);

	const float correction = pixelSize / 2.f;
	Vector3 cursor = pos - Vector3(correction, correction, 0.f);

	for (uint i = 0; string[i]; ++i) {
		const wchar_t chr = string[i];
		uint advance = printChar(access, chr, cursor, pixelSize, color);

		// kernings
		if (kernFirst_ <= chr && chr < kernCount_) {
			const i8* const kernMap = kernings_[chr - kernFirst_];
			const wchar_t chrNext = string[i + 1];

			if (kernMap && chrNext && kernMapFirst_ <= chrNext && chrNext < kernMapCount_)
				advance += kernMap[chrNext - kernMapFirst_];
		}

		cursor += Vector3(pixelSize * advance, 0.f, 0.f);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

