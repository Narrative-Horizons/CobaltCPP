#pragma once

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/macros.hpp>

namespace cobalt
{
	struct GraphicsContext::GraphicsContextImpl
	{
		Diligent::RefCntAutoPtr<Diligent::IRenderDevice>	device;
		Diligent::RefCntAutoPtr<Diligent::IDeviceContext>	immediateContext;
		Diligent::RefCntAutoPtr<Diligent::ISwapChain>		swapChain;
		Diligent::RENDER_DEVICE_TYPE						deviceType = Diligent::RENDER_DEVICE_TYPE_D3D11;

		const Window* window;
	};

	class GraphicsContextHelper
	{
		public:
			GraphicsContextHelper(const GraphicsContext& context);
			~GraphicsContextHelper() = default;

			COBALT_NO_COPY_MOVE(GraphicsContextHelper)

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IRenderDevice> getRenderDevice() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IDeviceContext> getImmediateContext() const;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::ISwapChain> getSwapchain() const;

		private:
			const GraphicsContext& _context;
	};
}
