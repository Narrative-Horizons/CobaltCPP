#include <cobalt/graphics/graphicscontext.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h>

#include "graphicscontexthelper.hpp"
#include "framebufferhelper.hpp"
#include "shaderhelper.hpp"
#include "vertexbufferhelper.hpp"
#include "indexbufferhelper.hpp"

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
				GetEngineFactoryVkType getEngineFactoryVk = LoadGraphicsEngineVk();
				EngineVkCreateInfo engineCi;

				_impl->deviceType = RENDER_DEVICE_TYPE_VULKAN;

				IEngineFactoryVk* pFactoryVk = getEngineFactoryVk();
				pFactoryVk->CreateDeviceAndContextsVk(engineCi, &_impl->device, &_impl->immediateContext);

#if defined(PLATFORM_WIN32)
				HWND hWnd = static_cast<HWND>(window.getNativeWindow());
				if (!_impl->swapChain && hWnd != nullptr)
				{
					Win32NativeWindow nativeWindow { hWnd };
					pFactoryVk->CreateSwapChainVk(_impl->device, _impl->immediateContext, scDesc, nativeWindow, &_impl->swapChain);
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

	void GraphicsContext::setRenderTarget(const UniquePtr<Framebuffer>& framebuffer, ResourceStateTransitionMode transitionMode) const
	{
		if (framebuffer == nullptr)
		{
			// Clear swapchain
			auto* rtv = _impl->swapChain->GetCurrentBackBufferRTV();
			_impl->immediateContext->SetRenderTargets(1, &rtv, 
				_impl->swapChain->GetDepthBufferDSV(), static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
		else
		{
			FramebufferHelper* framebufferHelper = new FramebufferHelper(*framebuffer);
			const uint32_t currentFrame = 0; // TODO: Make this the actual current frame

			_impl->immediateContext->SetRenderTargets(static_cast<uint32_t>(framebuffer->getInfo().renderTargets.size()),
				framebufferHelper->getRenderTargets(currentFrame),
				framebufferHelper->getDepthTarget(currentFrame),
				static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
	}

	void GraphicsContext::clearRenderTarget(const UniquePtr<Framebuffer>& framebuffer, const uint32_t index, const float* rgba, ResourceStateTransitionMode transitionMode) const
	{
		if(framebuffer == nullptr)
		{
			// Clear swapchain
			_impl->immediateContext->ClearRenderTarget(_impl->swapChain->GetCurrentBackBufferRTV(), rgba,
				static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
		else
		{
			FramebufferHelper* framebufferHelper = new FramebufferHelper(*framebuffer);
			const uint32_t currentFrame = 0; // TODO: Make this the actual current frame

			_impl->immediateContext->ClearRenderTarget(framebufferHelper->getRenderTarget(currentFrame, index), rgba,
				static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
	}

	void GraphicsContext::clearDepthStencil(const UniquePtr<Framebuffer>& framebuffer, ClearDepthStencilFlags flags, const float depth,
	                                        const uint8_t stencil, ResourceStateTransitionMode transitionMode) const
	{
		if(framebuffer == nullptr)
		{
			// Clear swapchain
			_impl->immediateContext->ClearDepthStencil(_impl->swapChain->GetDepthBufferDSV(), 
				static_cast<Diligent::CLEAR_DEPTH_STENCIL_FLAGS>(flags), depth, stencil, static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
		else
		{
			FramebufferHelper* framebufferHelper = new FramebufferHelper(*framebuffer);
			const uint32_t currentFrame = 0; // TODO: Make this the actual current frame

			_impl->immediateContext->ClearDepthStencil(framebufferHelper->getDepthTarget(currentFrame),
				static_cast<Diligent::CLEAR_DEPTH_STENCIL_FLAGS>(flags), depth, stencil, static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
	}

	void GraphicsContext::setPipelineState(Shader& shader) const
	{
		ShaderHelper* shaderHelper = new ShaderHelper(shader);
		_impl->immediateContext->SetPipelineState(shaderHelper->getPipeline());
	}

	void GraphicsContext::commitShaderResources(Shader& shader, ResourceStateTransitionMode transitionMode) const
	{
		ShaderHelper* shaderHelper = new ShaderHelper(shader);
		_impl->immediateContext->CommitShaderResources(shaderHelper->getResourceBinding(), static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
	}

	void GraphicsContext::setVertexBuffers(const uint32_t start, const std::vector<VertexBuffer*>& buffers, uint32_t* offsets,
	                                       ResourceStateTransitionMode transitionMode, SetVertexBufferFlags flags) const
	{
		std::vector<Diligent::IBuffer*> diligentBuffers;
		for(VertexBuffer* buf : buffers)
		{
			VertexBufferHelper* bufferHelper = new VertexBufferHelper(*buf);
			diligentBuffers.push_back(bufferHelper->getBuffer());
		}
		
		_impl->immediateContext->SetVertexBuffers(start, static_cast<uint32_t>(buffers.size()), &diligentBuffers[0], offsets,
			static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode), static_cast<Diligent::SET_VERTEX_BUFFERS_FLAGS>(flags));
	}

	void GraphicsContext::setIndexBuffer(IndexBuffer& buffer, const uint32_t byteOffset,
		ResourceStateTransitionMode transitionMode) const
	{
		IndexBufferHelper* bufferHelper = new IndexBufferHelper(buffer);
		_impl->immediateContext->SetIndexBuffer(bufferHelper->getBuffer(), byteOffset, static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
	}

	void GraphicsContext::drawIndexed(const DrawIndexedAttributes& attribs) const
	{
		Diligent::DrawIndexedAttribs attr;
		attr.BaseVertex = attribs.baseVertex;
		attr.FirstIndexLocation = attribs.firstIndexLocation;
		attr.FirstInstanceLocation = attribs.firstInstanceLocation;
		attr.Flags = static_cast<Diligent::DRAW_FLAGS>(attribs.flags);
		attr.IndexType = static_cast<Diligent::VALUE_TYPE>(attribs.indexType);
		attr.NumIndices = attribs.numIndices;
		attr.NumInstances = attribs.numInstances;

		_impl->immediateContext->DrawIndexed(attr);
	}

	void GraphicsContext::present() const
	{
		_impl->swapChain->Present(static_cast<uint32_t>(_impl->window->vSyncEnabled()));
	}

	void GraphicsContext::resize(const uint32_t width, const uint32_t height) const
	{
		_impl->swapChain->Resize(width, height);
	}
}