#include "graphicscontexthelper.hpp"

namespace cobalt
{
	GraphicsContextHelper::GraphicsContextHelper(const GraphicsContext& context) : _context(context) { }

	Diligent::RefCntAutoPtr<Diligent::IRenderDevice> GraphicsContextHelper::getRenderDevice()
	{
		return _context._impl->device;
	}

	Diligent::RefCntAutoPtr<Diligent::IDeviceContext> GraphicsContextHelper::getImmediateContext()
	{
		return _context._impl->immediateContext;
	}

	Diligent::RefCntAutoPtr<Diligent::ISwapChain> GraphicsContextHelper::getSwapchain()
	{
		return _context._impl->swapChain;
	}
}