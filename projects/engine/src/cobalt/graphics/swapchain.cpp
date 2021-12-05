#include <cobalt/graphics/swapchain.hpp>

namespace cobalt
{
	Swapchain::Swapchain(const UniquePtr<GraphicsContext>& context, SwapchainCreateInfo info)
	{
		const vkb::SwapchainBuilder bldr = vkb::SwapchainBuilder(context->_device)
			.set_desired_extent(info.width, info.height);

		const auto swapchainResult = bldr.build();
		if (!swapchainResult)
		{
			// TODO: Print error and exit
			exit(-1);
		}

		_swapchain = swapchainResult.value();

		const auto imageViews = _swapchain.get_image_views();
		if (imageViews.has_value())
		{
			for (auto view : imageViews.value())
			{
				ImageView* v = new ImageView();
				v->_count = 1;
				v->_imageView = view;

				
				_frameViews.push_back(v);
			}
		}
		else
		{
			destroy_swapchain(_swapchain);
			// TODO: Print error and exit
			exit(-1);
		}
	}

	Swapchain::~Swapchain()
	{
		destroy_swapchain(_swapchain);
	}
	
	Swapchain::Swapchain(Swapchain&& other) noexcept
	{
		
	}

	Swapchain& Swapchain::operator=(Swapchain&& other) noexcept
	{
		
	}

	ImageView* Swapchain::getImage(const uint32_t index) const noexcept
	{
		return _frameViews[index];
	}

	void Swapchain::present()
	{
		
	}

	void Swapchain::resize(uint32_t width, uint32_t height)
	{
		
	}
}