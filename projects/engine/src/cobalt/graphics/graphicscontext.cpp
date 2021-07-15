#include <cobalt/graphics/graphicscontext.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h>
#include <DiligentTools/Imgui/interface/ImGuiDiligentRenderer.hpp>

#include "graphicscontexthelper.hpp"
#include "framebufferhelper.hpp"
#include "shaderhelper.hpp"
#include "vertexbufferhelper.hpp"
#include "indexbufferhelper.hpp"

#include <cobalt/graphics/shader.hpp>
#include <cobalt/input.hpp>

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

		_impl->guiContext = ImGui::CreateContext();
		ImGui::StyleColorsDark();

		_impl->guiRenderer = new ImGuiDiligentRenderer(_impl->device, TEX_FORMAT_BGRA8_UNORM_SRGB, TEX_FORMAT_D32_FLOAT, 1024, 1024);
		_impl->guiRenderer->CreateFontsTexture();
	}

	GraphicsContext::~GraphicsContext()
	{
		if (!_impl)
			return;

		_impl->immediateContext->Flush();

		ImGui::DestroyContext(_impl->guiContext);
		_impl->guiContext = nullptr;
		
		_impl->guiRenderer->InvalidateDeviceObjects();
		delete _impl->guiRenderer;
		
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
			const FramebufferHelper framebufferHelper(*framebuffer);

			std::vector<Diligent::ITextureView*> views;
			views.reserve(framebuffer->getInfo().renderTargets.size());
			for(int index = 0; index < static_cast<int>(framebuffer->getInfo().renderTargets.size()); index++)
			{
				views.push_back(framebufferHelper.getRenderTarget(index, TextureTypeView::RENDER_TARGET));
			}

			auto x = framebufferHelper.getDepthTarget(TextureTypeView::DEPTH_STENCIL);

			_impl->immediateContext->SetRenderTargets(static_cast<uint32_t>(framebuffer->getInfo().renderTargets.size()),
				views.data(),
				x,
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
			const FramebufferHelper framebufferHelper(*framebuffer);

			_impl->immediateContext->ClearRenderTarget(framebufferHelper.getRenderTarget(index, TextureTypeView::RENDER_TARGET), rgba,
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
			const FramebufferHelper framebufferHelper(*framebuffer);

			_impl->immediateContext->ClearDepthStencil(framebufferHelper.getDepthTarget(TextureTypeView::DEPTH_STENCIL),
				static_cast<Diligent::CLEAR_DEPTH_STENCIL_FLAGS>(flags), depth, stencil, static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
	}

	void GraphicsContext::setPipelineState(Shader& shader) const
	{
		const ShaderHelper shaderHelper(shader);
		_impl->immediateContext->SetPipelineState(shaderHelper.getPipeline());
	}

	void GraphicsContext::commitShaderResources(Shader& shader, ResourceStateTransitionMode transitionMode) const
	{
		const ShaderHelper shaderHelper(shader);
		_impl->immediateContext->CommitShaderResources(shaderHelper.getResourceBinding(), static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
	}

	void GraphicsContext::setVertexBuffers(const uint32_t start, const std::vector<VertexBuffer*>& buffers, uint32_t* offsets,
	                                       ResourceStateTransitionMode transitionMode, SetVertexBufferFlags flags) const
	{
		std::vector<Diligent::IBuffer*> diligentBuffers;
		for(VertexBuffer* buf : buffers)
		{
			VertexBufferHelper bufferHelper(*buf);
			diligentBuffers.push_back(bufferHelper.getBuffer());
		}
		
		_impl->immediateContext->SetVertexBuffers(start, static_cast<uint32_t>(buffers.size()), diligentBuffers.data(), offsets,
			static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode), static_cast<Diligent::SET_VERTEX_BUFFERS_FLAGS>(flags));
	}

	void GraphicsContext::setIndexBuffer(IndexBuffer& buffer, const uint32_t byteOffset,
		ResourceStateTransitionMode transitionMode) const
	{
		const IndexBufferHelper bufferHelper(buffer);
		_impl->immediateContext->SetIndexBuffer(bufferHelper.getBuffer(), byteOffset, static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
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
		_impl->guiRenderer->NewFrame(1280, 720, Diligent::SURFACE_TRANSFORM_IDENTITY);
		_impl->guiRenderer->RenderDrawData(_impl->immediateContext, ImGui::GetDrawData());
		_impl->guiRenderer->EndFrame();

		_impl->swapChain->Present(static_cast<uint32_t>(_impl->window->vSyncEnabled()));
	}

	void GraphicsContext::resize(const uint32_t width, const uint32_t height) const
	{
		_impl->swapChain->Resize(width, height);
	}
}