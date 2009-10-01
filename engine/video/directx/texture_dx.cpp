#include "stdafx.h"

#ifdef VIDEO_DIRECTX

#include "video_system_dx.h"
#include "texture_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TextureDX::TextureDX(const TCHAR* const path)
: texture_(NULL) {
	assert(path);

	CHECKED_D3D_CALL(D3DXCreateTextureFromFile(&VideoDX::inst().device(), path, &texture_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TextureDX::~TextureDX() {
	if (texture_)
		texture_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TextureDX::activate(const unsigned stage) {
	assert(texture_);

	CHECKED_D3D_CALL(VideoDX::inst().device().SetTexture(stage, texture_));

	CHECKED_D3D_CALL(VideoDX::inst().device().SetTextureStageState(stage, D3DTSS_COLOROP, D3DTOP_MODULATE));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetTextureStageState(stage, D3DTSS_COLORARG1, D3DTA_TEXTURE));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetTextureStageState(stage, D3DTSS_COLORARG2, D3DTA_DIFFUSE));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetTextureStageState(stage, D3DTSS_ALPHAOP, D3DTOP_DISABLE));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
