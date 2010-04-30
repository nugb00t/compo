#include "stdafx.h"

#include "video_assets_d3d9.h"

#include "filesystem/files.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoAssetsD3D9::reset() {
	while (textureCount_--)
		textures_[textureCount_].texture->Release();

#ifndef TRACK_DIRECTORY_CHANGES
	textureLoadQueue_.reset();
#endif

	pool_.reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const uint VideoAssetsD3D9::addTexture(const TCHAR* const path) {
	assert(textureCount_ < MAX_TEXTURES);

	uint file;
	if (Files::inst().add(path, pool_, file)) {
		textures_[textureCount_].path = path;
		textures_[textureCount_].file = file;
		textures_[textureCount_].texture = NULL;

		Files::inst().get(file).object = textureCount_;		// back reference

#ifndef TRACK_DIRECTORY_CHANGES
		textureLoadQueue_.add(TextureQueueItem(textureCount_, textures_[textureCount_].file));
#endif

		return textureCount_++;
	} else {
		const uint texture = Files::inst().get(file).object;
		assert(0 <= texture && texture < textureCount_);

		return texture;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoAssetsD3D9::update(IDirect3DDevice9* device) {
	assert(device);

#ifndef TRACK_DIRECTORY_CHANGES
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
#else
	for (uint i = 0; i < textureCount_; ++i) {
		File& item = Files::inst().get(textures_[i].file);

		assert(item.status != File::Error);

		if (item.status == File::Aquired) {
			CHECKED_D3D_CALL_A(D3DXCreateTextureFromFileInMemory(device, item.buffer, item.size, &textures_[i].texture));
			item.status = File::Processed;
		}
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
