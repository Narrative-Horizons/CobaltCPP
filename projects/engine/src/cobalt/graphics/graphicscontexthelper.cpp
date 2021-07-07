#include "graphicscontexthelper.hpp"

namespace cobalt
{
	GraphicsContextHelper::GraphicsContextHelper(const GraphicsContext& context) : _context(context) { }

	Diligent::RefCntAutoPtr<Diligent::IRenderDevice> GraphicsContextHelper::getRenderDevice() const
	{
		return _context._impl->device;
	}

	Diligent::RefCntAutoPtr<Diligent::IDeviceContext> GraphicsContextHelper::getImmediateContext() const
	{
		return _context._impl->immediateContext;
	}

	Diligent::RefCntAutoPtr<Diligent::ISwapChain> GraphicsContextHelper::getSwapchain() const
	{
		return _context._impl->swapChain;
	}
}