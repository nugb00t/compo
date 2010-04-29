#include "stdafx.h"

#include "video_assets_d3d9.h"

#include "filesystem/files.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoAssetsD3D9::reset() {
	while (textureCount_--)
		textures_[textureCount_].texture->Release();

	textureLoadQueue_.reset();
	pool_.reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const uint VideoAssetsD3D9::addTexture(const TCHAR* const path) {
	assert(textureCount_ < MAX_TEXTURES);

	textures_[textureCount_].path = path;
	textures_[textureCount_].file = Files::inst().add(path, pool_);
	textures_[textureCount_].texture = NULL;

	textureLoadQueue_.add(TextureQueueItem(textureCount_, textures_[textureCount_].file));
	
	return textureCount_++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoAssetsD3D9::update(IDirect3DDevice9* device) {
	assert(device);

	for (TextureLoadQueue::Range range(textureLoadQueue_); !range.finished(); range.next()) {
		File& item = Files::inst().get(range.get().file);

		assert(item.status != File::Error);
		
		if (item.status == File::Aquired) {
			CHECKED_D3D_CALL_A(D3DXCreateTextureFromFileInMemory(device, 
																 item.buffer,
																 item.size,
																 &textures_[range.get().texture].texture));
			item.status = File::Processed;
			range.remove();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
