#pragma once

#include <cobalt/macros.hpp>
#include <VkBootstrap.h>

#include <cobalt/containers/smartpointers.hpp>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/imageview.hpp>

namespace cobalt
{
	struct SwapchainCreateInfo
	{
		uint32_t width;
		uint32_t height;
	};
	
	class Swapchain
	{
		public:
			Swapchain(const UniquePtr<GraphicsContext>& context, SwapchainCreateInfo info);
			~Swapchain();

			COBALT_NO_COPY(Swapchain)

			Swapchain(Swapchain&& other) noexcept;
			Swapchain& operator=(Swapchain&& other) noexcept;

			COBALT_NO_DISCARD ImageView* getImage(uint32_t index) const noexcept;

			void present();

			void resize(uint32_t width, uint32_t height);

		private:
			vkb::Swapchain _swapchain;
			std::vector<ImageView*> _frameViews;
	};
}
