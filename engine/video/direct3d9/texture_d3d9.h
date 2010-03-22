#pragma once

#include "video/texture.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TextureD3D9 : public Texture {
public:
	TextureD3D9(const TCHAR* const path);
	~TextureD3D9();

	// interface: Texture
	virtual bool initialize();
	virtual void activate(const uint stage);

    virtual const TCHAR* path() const { return path_; }

    // own
    IDirect3DTexture9* d3dObject() const { return texture_; }

private:
	IDirect3DTexture9* texture_;
    const TCHAR* path_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
