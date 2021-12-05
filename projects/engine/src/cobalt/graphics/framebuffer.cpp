#include <cobalt/graphics/framebuffer.hpp>

#include <cobalt/graphics/graphicscontext.hpp>

namespace cobalt
{
	Framebuffer::Framebuffer(const UniquePtr<GraphicsContext>& context, const FramebufferCreateInfo& createInfo) : _context(context)
	{
		_createInfo = createInfo;

		resize(createInfo.width, createInfo.height);
	}

	FramebufferCreateInfo Framebuffer::getInfo() const
	{
		return _createInfo;
	}

	void Framebuffer::resize(const uint32_t width, const uint32_t height)
	{
		_createInfo.width = width;
		_createInfo.height = height;
	}
}

