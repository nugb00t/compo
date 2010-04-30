#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoAssetsD3D9 {
	static const uint MAX_TEXTURES = 32;
	
	//-----------------------------------------------------------------------------------------------------------------

	struct Texture {
		IDirect3DTexture9* texture;
		const TCHAR* path;
		uint file;
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	VideoAssetsD3D9(const uint bufferSize) : pool_(bufferSize), textureCount_(0) {}

	// interface: own
	void reset();
	const uint addTexture(const TCHAR* const path);
	void update(IDirect3DDevice9* device);

	IDirect3DTexture9* getTexture(const uint i) { return textures_[i].texture; }

private:
	kaynine::MemoryPool pool_;

	// textures
	Texture textures_[MAX_TEXTURES];
	uint textureCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
