#pragma once

#include "../video_assets.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VideoAssetsD3D9 : public VideoAssets {
	static const uint MAX_TEXTURES = 32;

	//-----------------------------------------------------------------------------------------------------------------

	struct Texture {
		IDirect3DTexture9* texture;
		const TCHAR* path;
		uint resource;
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	VideoAssetsD3D9(const uint bufferSize) : pool_(bufferSize), textureCount_(0) {}

	// interface: VideoAssets
	virtual void reset();
	virtual const uint addTexture(const TCHAR* const path);
	virtual void update();

private:
	kaynine::MemoryPool pool_;

	Texture textures_[MAX_TEXTURES];
	uint textureCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
