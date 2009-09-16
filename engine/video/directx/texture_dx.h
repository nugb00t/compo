#ifndef TEXTURE_DX_INCLUDED
#define TEXTURE_DX_INCLUDED

#include "video/texture.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TextureDX : public Texture {
public:
	TextureDX();
	~TextureDX();

	// interface: Texture
	virtual bool load(const TCHAR* const path);
	virtual void update();

private:
	bool doLoad();

private:
	IDirect3DSurface9* surface_;
	const TCHAR* path_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
