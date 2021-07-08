#include <cobalt/graphics/framebuffer.hpp>

#include "framebufferhelper.hpp"

namespace cobalt
{
	Framebuffer::Framebuffer(const FramebufferCreateInfo& createInfo)
	{
		_impl = new FramebufferImpl();
		_createInfo = createInfo;

		// TODO: Create textureviews
	}

	FramebufferCreateInfo Framebuffer::getInfo() const
	{
		return _createInfo;
	}
}

