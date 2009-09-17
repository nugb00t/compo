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
	virtual void activate(const unsigned channel);

private:
	IDirect3DTexture9* texture_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
