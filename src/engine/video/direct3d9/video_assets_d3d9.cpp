#include "stdafx.h"

#include "video_d3d9.h"
#include "video_assets_d3d9.h"

#include "filesystem/resources.h"

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
	textures_[textureCount_].resource = Resources::inst().add(path, pool_);
	textures_[textureCount_].texture = NULL;

	textureLoadQueue_.add(TextureQueueItem(textureCount_, textures_[textureCount_].resource));
	
	return textureCount_++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoAssetsD3D9::update(Video& video) {
	for (TextureLoadQueue::Range range(textureLoadQueue_); !range.finished(); range.next()) {
		const Resource& item = Resources::inst().get(range.get().resource);

		assert(item.status != Resource::Error);
		
		if (item.status == Resource::Done) {
			VideoD3D9* videoD3D9 = reinterpret_cast<VideoD3D9*>(&video);
			assert(videoD3D9);
			
			CHECKED_D3D_CALL_A(D3DXCreateTextureFromFile(videoD3D9->device(), path_, &textures_[range.get().texture].texture));

			range.remove();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
