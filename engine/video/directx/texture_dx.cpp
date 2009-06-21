#include "stdafx.h"

#ifdef VIDEO_DIRECTX

#include "video_system_dx.h"
#include "texture_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TextureDX::TextureDX()
: surface_(NULL), path_(NULL) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TextureDX::load(const TCHAR* const path) {
	path_ = path;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TextureDX::update() {
	if (!surface_) {
		DEBUG_ONLY(bool ok = )
			doLoad();
		assert(ok);
	}

	if (surface_) {
		IDirect3DSurface9* backBuffer = NULL;
		VideoDX::get().device().GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
		VideoDX::get().device().UpdateSurface(surface_, NULL, backBuffer, NULL);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TextureDX::doLoad() {
	if (!path_)
		return false;

	D3DXIMAGE_INFO info;
	HRESULT res = D3DXGetImageInfoFromFile(path_, &info);
	if (res != D3D_OK)
		return false;

	res = VideoDX::get().device().CreateOffscreenPlainSurface(info.Width, info.Height, info.Format, D3DPOOL_DEFAULT, &surface_, NULL);
	if (res != D3D_OK)
		return false;

	res = D3DXLoadSurfaceFromFile(surface_, NULL, NULL, path_, NULL, D3DX_FILTER_NONE, 0, NULL);
	if (res != D3D_OK) {
		// TODO: release surface_
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
