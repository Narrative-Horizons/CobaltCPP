#include <cobalt/graphics/framebufferhelper.hpp>

namespace cobalt
{
	FramebufferHelper::FramebufferHelper(const Framebuffer& framebuffer) : _framebuffer(framebuffer) { }

	Diligent::ITexture** FramebufferHelper::getRenderTargets() const
	{
		return &_framebuffer._impl->renderTargets[0];
	}

	Diligent::ITextureView* FramebufferHelper::getRenderTarget(const uint32_t index, TextureTypeView viewType) const
	{
		return _framebuffer._impl->renderTargets[index]->GetDefaultView(static_cast<Diligent::TEXTURE_VIEW_TYPE>(viewType));
	}

	Diligent::ITextureView* FramebufferHelper::getDepthTarget(TextureTypeView viewType) const
	{
		return _framebuffer._impl->depthTarget->GetDefaultView(static_cast<Diligent::TEXTURE_VIEW_TYPE>(viewType));
	}
}
