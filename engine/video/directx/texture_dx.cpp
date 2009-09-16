#include "stdafx.h"

#ifdef VIDEO_DIRECTX

#include "video_system_dx.h"
#include "texture_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TextureDX::TextureDX()
: surface_(NULL), path_(NULL) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TextureDX::~TextureDX() {
	//if (surface_)
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TextureDX::load(const TCHAR* const path) {
	path_ = path;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TextureDX::update() {
	if (!surface_) {
		CHECKED_CALL(doLoad());
	}

	if (surface_) {
		IDirect3DSurface9* backBuffer = NULL;

		CHECKED_D3D_CALL(VideoDX::inst().device().GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer));
		CHECKED_D3D_CALL(VideoDX::inst().device().UpdateSurface(surface_, NULL, backBuffer, NULL));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TextureDX::doLoad() {
	if (!path_)
		return false;

	D3DXIMAGE_INFO info;
	CHECKED_D3D_CALL(D3DXGetImageInfoFromFile(path_, &info));

	CHECKED_D3D_CALL(VideoDX::inst().device().CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8/*info.Format*/, D3DPOOL_SYSTEMMEM, &surface_, NULL));

	if (D3DXLoadSurfaceFromFile(surface_, NULL, NULL, path_, NULL, D3DX_FILTER_NONE, 0, NULL) != D3D_OK) {
		// TODO: release surface_
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
