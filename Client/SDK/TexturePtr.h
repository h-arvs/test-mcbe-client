#pragma once
#include <memory>
#include "ResourceLocation.h"

namespace mce {
	class TexturePtr {
	public:
		std::shared_ptr<class BedrockTextureData> mClientTexture;
		std::shared_ptr<ResourceLocation> mResourceLocation;
	};
}