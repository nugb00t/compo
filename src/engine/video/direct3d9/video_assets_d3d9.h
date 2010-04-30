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

#ifndef TRACK_DIRECTORY_CHANGES
		struct TextureQueueItem {
			uint texture;
			uint file;

			TextureQueueItem() {}

			TextureQueueItem(const uint texture_, const uint file_)
				: texture(texture_), file(file_) {}
		};

		typedef kaynine::StaticList<TextureQueueItem, MAX_TEXTURES> TextureLoadQueue;
#endif

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

#ifndef TRACK_DIRECTORY_CHANGES
		TextureLoadQueue textureLoadQueue_;
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
