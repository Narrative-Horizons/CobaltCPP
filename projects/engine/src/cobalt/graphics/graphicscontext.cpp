#include <cobalt/graphics/graphicscontext.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h>

#include "graphicscontexthelper.hpp"
#include "framebufferhelper.hpp"

#include <cobalt/graphics/shader.hpp>

namespace cobalt
{
	GraphicsContext::GraphicsContext(const Window& window, GraphicsContextCreateInfo createInfo)
	{
		using namespace Diligent;

		_impl = new GraphicsContextImpl();
		_impl->window = &window;
		
		SwapChainDesc scDesc;

		switch (createInfo.api)
		{
			case GraphicsAPI::Vulkan:
			{
				GetEngineFactoryVkType GetEngineFactoryVk = LoadGraphicsEngineVk();
				EngineVkCreateInfo EngineCI;

				_impl->deviceType = RENDER_DEVICE_TYPE_VULKAN;

				IEngineFactoryVk* pFactoryVk = GetEngineFactoryVk();
				pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &_impl->device, &_impl->immediateContext);

#if defined(PLATFORM_WIN32)
				HWND hWnd = static_cast<HWND>(window.getNativeWindow());
				if (!_impl->swapChain && hWnd != nullptr)
				{
					Win32NativeWindow Window { hWnd };
					pFactoryVk->CreateSwapChainVk(_impl->device, _impl->immediateContext, scDesc, Window, &_impl->swapChain);
				}
#endif
				break;
			}

			case GraphicsAPI::OpenGL: 
			case GraphicsAPI::DX11: 
			case GraphicsAPI::DX12: 
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

	void GraphicsContext::setRenderTarget(Framebuffer& framebuffer, ResourceStateTransitionMode transitionMode) const
	{
		FramebufferHelper* framebufferHelper = new FramebufferHelper(framebuffer);
		const uint32_t currentFrame = 0; // TODO: Make this the actual current frame
		
		_impl->immediateContext->SetRenderTargets(static_cast<uint32_t>(framebuffer.getInfo().renderTargets.size()),
			framebufferHelper->getRenderTargets(currentFrame),
			framebufferHelper->getDepthTarget(currentFrame),
			static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
	}

	void GraphicsContext::setPipelineState(Shader& shader)
	{
		
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