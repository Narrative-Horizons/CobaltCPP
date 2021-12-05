#include <cobalt/graphics/image.hpp>

namespace cobalt
{
	Image::Image(const UniquePtr<GraphicsContext>& context, ImageCreateInfo info, ImageMemoryCreateInfo memoryInfo, const std::string& name,
		const uint32_t frame)
	{
		const std::string objectName = std::string(name) + "_" + std::to_string(frame);
		if (context->_images.find(objectName) != context->_images.end())
		{
			context->_images[objectName]->_count++;
		}

		_count = 1;

		VkImageCreateInfo imageInfo;
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.flags = 0;
		imageInfo.pNext = nullptr;
		imageInfo.arrayLayers = info.arrayLayers;
		imageInfo.extent = VkExtent3D{ info.width, info.height, info.depth };
		imageInfo.imageType = static_cast<VkImageType>(info.imageType);
		imageInfo.format = static_cast<VkFormat>(info.format);
		imageInfo.queueFamilyIndexCount = info.queueFamilyIndexCount;
		imageInfo.pQueueFamilyIndices = info.queueFamilyIndices;
		imageInfo.mipLevels = info.mipLevels;
		imageInfo.initialLayout = static_cast<VkImageLayout>(info.initialLayout);
		imageInfo.sharingMode = static_cast<VkSharingMode>(info.sharingMode);
		imageInfo.tiling = static_cast<VkImageTiling>(info.tiling);
		imageInfo.samples = static_cast<VkSampleCountFlagBits>(info.samples);
		imageInfo.usage = info.usage;

		VmaAllocationCreateInfo allocInfo = {};
		allocInfo.pUserData = nullptr;
		allocInfo.flags = 0;
		allocInfo.usage = static_cast<VmaMemoryUsage>(memoryInfo.usage);
		allocInfo.preferredFlags = memoryInfo.preferredFlags;
		allocInfo.requiredFlags = memoryInfo.requiredFlags;

		vmaCreateImage(context->_allocator, &imageInfo, &allocInfo, &_image, &_allocation, nullptr);

		context->_images[objectName] = this;
	}

	Image::~Image()
	{
		
	}
}
