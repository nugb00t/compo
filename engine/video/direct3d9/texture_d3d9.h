#ifndef TEXTURE_D3D9_INCLUDED
#define TEXTURE_D3D9_INCLUDED

#include "video/texture.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TextureD3D9 : public Texture {
public:
	TextureD3D9(const TCHAR* const path);
	~TextureD3D9();

	// interface: Texture
	virtual void activate(const unsigned stage);

    virtual const TCHAR* path() const { return path_; }

    // own
    IDirect3DTexture9* d3dObject() const { return texture_; }

private:
	IDirect3DTexture9* texture_;
    const TCHAR* path_;
};

typedef boost::intrusive_ptr<TextureD3D9> TextureDXPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
