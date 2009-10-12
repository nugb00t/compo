#ifndef TEXTURE_DX_INCLUDED
#define TEXTURE_DX_INCLUDED

#include "video/texture.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TextureDX : public Texture {
public:
	TextureDX(const TCHAR* const path);
	~TextureDX();

	// interface: Texture
	virtual void activate(const unsigned stage);

    virtual const TCHAR* path() const { return path_; }

    // own
    IDirect3DTexture9* d3dObject() const { return texture_; }

private:
	IDirect3DTexture9* texture_;
    const TCHAR* path_;
};

typedef boost::intrusive_ptr<TextureDX> TextureDXPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
