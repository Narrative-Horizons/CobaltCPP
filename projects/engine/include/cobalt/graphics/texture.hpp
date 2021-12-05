#pragma once

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/graphics/image.hpp>
#include <cobalt/resources/resourcemanager.hpp>

namespace cobalt
{
	struct TextureCreateInfo
	{
		std::string name;
		Usage usage = Usage::IMMUTABLE;
		BindFlags bindFlags = BindFlags::SHADER_RESOURCE;
		uint32_t mipLevels = 0;
		CPUAccessFlags accessFlags = CPUAccessFlags::NONE;
		bool isSRGB = false;
		bool generateMips = true;
		TextureFormat format = TextureFormat::UNKNOWN;
	};
	
	class Texture final : public Resource
	{
		public:

		private:
			friend class ResourceManager;
		
			Texture(const UniquePtr<GraphicsContext>& context, const UniquePtr<Image>& image, const TextureCreateInfo& createInfo);
		
			const UniquePtr<Image>& _image;
	};
}
