#include "stdafx.h"

#ifdef VIDEO_DIRECTX

#include "video_system_dx.h"
#include "texture_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TextureDX::TextureDX()
: texture_(NULL) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TextureDX::~TextureDX() {
	if (texture_)
		texture_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TextureDX::load(const TCHAR* const path) {
	assert(path);

	return D3DXCreateTextureFromFile(&VideoDX::inst().device(), path, &texture_) == D3D_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TextureDX::activate(const unsigned channel) {
	assert(texture_);

	CHECKED_D3D_CALL(VideoDX::inst().device().SetTexture(channel, texture_));

	CHECKED_D3D_CALL(VideoDX::inst().device().SetTextureStageState(channel, D3DTSS_COLOROP, D3DTOP_MODULATE));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetTextureStageState(channel, D3DTSS_COLORARG1, D3DTA_TEXTURE));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetTextureStageState(channel, D3DTSS_COLORARG2, D3DTA_DIFFUSE));
	CHECKED_D3D_CALL(VideoDX::inst().device().SetTextureStageState(channel, D3DTSS_ALPHAOP, D3DTOP_DISABLE));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
