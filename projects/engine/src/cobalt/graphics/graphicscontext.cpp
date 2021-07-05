#include <cobalt/graphics/graphicscontext.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h>

#include "graphicscontexthelper.hpp"

namespace cobalt
{
	GraphicsContext::GraphicsContext(const Window& window, GraphicsContextCreateInfo createInfo)
	{
		using namespace Diligent;

		_impl = new GraphicsContext::GraphicsContextImpl();
		_impl->window = &window;
		
		SwapChainDesc SCDesc;

		switch (createInfo.api)
		{
			case GraphicsAPI::Vulkan:
			{
				GetEngineFactoryVkType GetEngineFactoryVk = LoadGraphicsEngineVk();
				EngineVkCreateInfo EngineCI;

				IEngineFactoryVk* pFactoryVk = GetEngineFactoryVk();
				pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &_impl->device, &_impl->immediateContext);

#if defined(PLATFORM_WIN32)
				HWND hWnd = static_cast<HWND>(window.getNativeWindow());
				if (!_impl->swapChain && hWnd != nullptr)
				{
					Win32NativeWindow Window { hWnd };
					pFactoryVk->CreateSwapChainVk(_impl->device, _impl->immediateContext, SCDesc, Window, &_impl->swapChain);
				}
#endif
				break;
			}

			default:
			{
				std::cerr << "API Currently not supported" << std::endl;
				break;
			}
		}
	}

	GraphicsContext::~GraphicsContext()
	{
		if (!_impl)
			return;

		_impl->immediateContext->Flush();

		delete _impl;
	}

	GraphicsContext::GraphicsContext(GraphicsContext&& other) noexcept
	{
		_impl = other._impl;
		other._impl = nullptr;
	}

	GraphicsContext& GraphicsContext::operator=(GraphicsContext&& other) noexcept
	{
		if (_impl != nullptr)
		{
			_impl->immediateContext->Flush();

			delete _impl;
		}

		_impl = other._impl;
		other._impl = nullptr;

		return *this;
	}
	
	void GraphicsContext::present() const
	{
		_impl->swapChain->Present(static_cast<uint32_t>(_impl->window->vSyncEnabled()));
	}

	void GraphicsContext::resize(uint32_t width, uint32_t height) const
	{
		_impl->swapChain->Resize(width, height);
	}
}