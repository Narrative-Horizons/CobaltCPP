#include "framebufferhelper.hpp"

namespace cobalt
{
	FramebufferHelper::FramebufferHelper(const Framebuffer& framebuffer) : _framebuffer(framebuffer) { }

	Diligent::ITextureView** FramebufferHelper::getRenderTargets(const uint32_t frame) const
	{
		return &_framebuffer._impl->renderTargets[frame][0];
	}

	Diligent::ITextureView* FramebufferHelper::getRenderTarget(const uint32_t frame, const uint32_t index) const
	{
		return _framebuffer._impl->renderTargets[frame][index];
	}

	Diligent::ITextureView* FramebufferHelper::getDepthTarget(const uint32_t frame) const
	{
		return _framebuffer._impl->depthTarget[frame];
	}
}