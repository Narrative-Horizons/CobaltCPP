#pragma once

#include <cobalt/containers/smartpointers.hpp>
#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/image.hpp>

#include <cobalt/macros.hpp>
#include <VkBootstrap.h>

namespace cobalt
{
	struct ImageViewCreateInfo
	{
		Image* image;
		uint32_t viewType;
		uint32_t format;
		uint32_t aspectMask;
		uint32_t baseMipLevel;
		uint32_t levelCount;
		uint32_t baseArrayLayer;
		uint32_t layerCount;
	};

	class ImageView
	{
		public:
			ImageView() = default;
			ImageView(const UniquePtr<GraphicsContext>& context, ImageViewCreateInfo info, const std::string& name, const uint32_t frame);
			~ImageView();

			COBALT_NO_COPY(ImageView)

			ImageView(ImageView&& other) noexcept;
			ImageView& operator=(ImageView&& other) noexcept;

		private:
			friend class Swapchain;
		
			VkImageView _imageView;
			uint32_t _count;
	};
}
