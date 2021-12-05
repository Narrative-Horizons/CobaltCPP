#include <cobalt/graphics/imageview.hpp>

namespace cobalt
{
	ImageView::ImageView(const UniquePtr<GraphicsContext>& context, ImageViewCreateInfo info, const std::string& name, const uint32_t frame)
	{
		const std::string objectName = std::string(name) + "_" + std::to_string(frame);
		if (context->_imageViews.find(objectName) != context->_imageViews.end())
		{
			context->_imageViews[objectName]->_count++;
		}

		_count = 1;

		VkImageViewCreateInfo viewInfo = {};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.flags = 0;
		viewInfo.pNext = nullptr;
		viewInfo.format = static_cast<VkFormat>(info.format);
		viewInfo.image = info.image;
		viewInfo.subresourceRange = VkImageSubresourceRange
		{
			info.aspectMask,
			info.baseMipLevel,
			info.levelCount,
			info.baseArrayLayer,
			info.layerCount
		};

		viewInfo.viewType = static_cast<VkImageViewType>(info.viewType);

		device->functionTable.createImageView(&viewInfo, device->device.allocation_callbacks, &view->imageView);
		device->imageViews[objectName] = view;

		return view;
	}

	ImageView::~ImageView()
	{
		
	}

	ImageView::ImageView(ImageView&& other) noexcept
	{
		
	}

	ImageView& ImageView::operator=(ImageView&& other) noexcept
	{
		
	}
}
