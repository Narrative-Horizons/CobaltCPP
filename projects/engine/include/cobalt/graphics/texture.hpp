#pragma once

#include <cobalt/graphics/shader.hpp>
#include <cobalt/graphics/image.hpp>

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
	
	class Texture : public ShaderResource
	{
		public:
			Texture(const GraphicsContext& context, const Image& image, const TextureCreateInfo& createInfo);
			~Texture();

		private:
			friend class TextureHelper;

			struct TextureImpl;
			TextureImpl* _timpl;
		
			const Image& _image;
	};
}