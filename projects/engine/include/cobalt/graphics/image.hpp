#pragma once

#include <string>

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/graphics/graphicscontext.hpp>

namespace cobalt
{
	struct ImageCreateInfo
	{
		uint32_t imageType;
		uint32_t format;
		uint32_t width;
		uint32_t height;
		uint32_t depth;
		uint32_t mipLevels;
		uint32_t arrayLayers;
		uint32_t samples;
		uint32_t tiling;
		uint32_t usage;
		uint32_t sharingMode;
		uint32_t queueFamilyIndexCount;
		uint32_t* queueFamilyIndices;
		uint32_t initialLayout;
		uint32_t memoryUsage;
	};

	struct ImageMemoryCreateInfo
	{
		uint32_t usage;
		uint32_t preferredFlags;
		uint32_t requiredFlags;
	};
	
	class Image
	{
		public:
			explicit Image(const UniquePtr<GraphicsContext>& context, ImageCreateInfo info, ImageMemoryCreateInfo memoryInfo, const std::string& name, const uint32_t frame);
			~Image();

		private:
			VkImage _image;
			uint32_t _count;
			VmaAllocation _allocation;
	};
}
