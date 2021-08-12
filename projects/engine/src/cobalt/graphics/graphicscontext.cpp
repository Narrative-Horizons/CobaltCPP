#include <cobalt/graphics/graphicscontext.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h>
#include <DiligentTools/Imgui/interface/ImGuiDiligentRenderer.hpp>

#include <cobalt/graphics/shader.hpp>
#include <cobalt/input.hpp>

namespace cobalt
{
	GraphicsContext::GraphicsContext(const Window& window, GraphicsContextCreateInfo createInfo)
	{
		using namespace Diligent;

		SwapChainDesc scDesc;

		_window = &window;

		switch (createInfo.api)
		{
			case GraphicsAPI::Vulkan:
			{
				GetEngineFactoryVkType getEngineFactoryVk = LoadGraphicsEngineVk();
				EngineVkCreateInfo engineCi;

				_deviceType = RENDER_DEVICE_TYPE_VULKAN;

				IEngineFactoryVk* pFactoryVk = getEngineFactoryVk();
				pFactoryVk->CreateDeviceAndContextsVk(engineCi, &_device, &_immediateContext);

#if defined(PLATFORM_WIN32)
				HWND hWnd = static_cast<HWND>(window.getNativeWindow());
				if (!_swapChain && hWnd != nullptr)
				{
					Win32NativeWindow nativeWindow { hWnd };
					pFactoryVk->CreateSwapChainVk(_device, _immediateContext, scDesc, nativeWindow, &_swapChain);
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

		_guiContext = ImGui::CreateContext();
		ImGui::StyleColorsDark();

		_guiRenderer = new ImGuiDiligentRenderer(_device, TEX_FORMAT_BGRA8_UNORM_SRGB, TEX_FORMAT_D32_FLOAT, 1024, 1024);
		_guiRenderer->CreateFontsTexture();
	}

	GraphicsContext::~GraphicsContext()
	{
		_immediateContext->Flush();

		ImGui::DestroyContext(_guiContext);
		_guiContext = nullptr;
		
		_guiRenderer->InvalidateDeviceObjects();
		delete _guiRenderer;
	}

	GraphicsContext::GraphicsContext(GraphicsContext&& other) noexcept
	{
	}

	GraphicsContext& GraphicsContext::operator=(GraphicsContext&& other) noexcept
	{
		_immediateContext->Flush();

		return *this;
	}

	void GraphicsContext::setRenderTarget(const UniquePtr<Framebuffer>& framebuffer, ResourceStateTransitionMode transitionMode)
	{
		if (framebuffer == nullptr)
		{
			// Clear swapchain
			auto* rtv = _swapChain->GetCurrentBackBufferRTV();
			_immediateContext->SetRenderTargets(1, &rtv, 
				_swapChain->GetDepthBufferDSV(), static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
		else
		{
			std::vector<Diligent::ITextureView*> views;
			views.reserve(framebuffer->getInfo().renderTargets.size());
			for(int index = 0; index < static_cast<int>(framebuffer->getInfo().renderTargets.size()); index++)
			{
				views.push_back(framebuffer->getRenderTarget(index, TextureTypeView::RENDER_TARGET));
			}

			auto x = framebuffer->getDepthTarget(TextureTypeView::DEPTH_STENCIL);

			_immediateContext->SetRenderTargets(static_cast<uint32_t>(framebuffer->getInfo().renderTargets.size()),
				views.data(),
				x,
				static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
	}

	void GraphicsContext::clearRenderTarget(const UniquePtr<Framebuffer>& framebuffer, const uint32_t index, const float* rgba, ResourceStateTransitionMode transitionMode)
	{
		if(framebuffer == nullptr)
		{
			// Clear swapchain
			_immediateContext->ClearRenderTarget(_swapChain->GetCurrentBackBufferRTV(), rgba,
				static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
		else
		{
			_immediateContext->ClearRenderTarget(framebuffer->getRenderTarget(index, TextureTypeView::RENDER_TARGET), rgba,
				static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
	}

	void GraphicsContext::clearDepthStencil(const UniquePtr<Framebuffer>& framebuffer, ClearDepthStencilFlags flags, const float depth,
	                                        const uint8_t stencil, ResourceStateTransitionMode transitionMode)
	{
		if(framebuffer == nullptr)
		{
			// Clear swapchain
			_immediateContext->ClearDepthStencil(_swapChain->GetDepthBufferDSV(), 
				static_cast<Diligent::CLEAR_DEPTH_STENCIL_FLAGS>(flags), depth, stencil, static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
		else
		{
			_immediateContext->ClearDepthStencil(framebuffer->getDepthTarget(TextureTypeView::DEPTH_STENCIL),
				static_cast<Diligent::CLEAR_DEPTH_STENCIL_FLAGS>(flags), depth, stencil, static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
		}
	}

	void GraphicsContext::setPipelineState(Shader& shader)
	{
		_immediateContext->SetPipelineState(shader.getPipeline());
	}

	void GraphicsContext::commitShaderResources(Shader& shader, ResourceStateTransitionMode transitionMode)
	{
		_immediateContext->CommitShaderResources(shader.getResourceBinding(), static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
	}

	void GraphicsContext::setVertexBuffers(const uint32_t start, const std::vector<VertexBuffer*>& buffers, uint32_t* offsets,
	                                       ResourceStateTransitionMode transitionMode, SetVertexBufferFlags flags)
	{
		std::vector<Diligent::IBuffer*> diligentBuffers;
		for(VertexBuffer* buf : buffers)
		{
			diligentBuffers.push_back(buf->getBuffer());
		}
		
		_immediateContext->SetVertexBuffers(start, static_cast<uint32_t>(buffers.size()), diligentBuffers.data(), offsets,
			static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode), static_cast<Diligent::SET_VERTEX_BUFFERS_FLAGS>(flags));
	}

	void GraphicsContext::setIndexBuffer(IndexBuffer& buffer, const uint32_t byteOffset,
		ResourceStateTransitionMode transitionMode)
	{
		_immediateContext->SetIndexBuffer(buffer.getBuffer(), byteOffset, static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));
	}

	void GraphicsContext::drawIndexed(const DrawIndexedAttributes& attribs)
	{
		Diligent::DrawIndexedAttribs attr;
		attr.BaseVertex = attribs.baseVertex;
		attr.FirstIndexLocation = attribs.firstIndexLocation;
		attr.FirstInstanceLocation = attribs.firstInstanceLocation;
		attr.Flags = static_cast<Diligent::DRAW_FLAGS>(attribs.flags);
		attr.IndexType = static_cast<Diligent::VALUE_TYPE>(attribs.indexType);
		attr.NumIndices = attribs.numIndices;
		attr.NumInstances = attribs.numInstances;

		_immediateContext->DrawIndexed(attr);
	}

	void GraphicsContext::present()
	{
		_guiRenderer->NewFrame(1280, 720, Diligent::SURFACE_TRANSFORM_IDENTITY);
		_guiRenderer->RenderDrawData(_immediateContext, ImGui::GetDrawData());
		_guiRenderer->EndFrame();

		_swapChain->Present(static_cast<uint32_t>(_window->vSyncEnabled()));
	}

	void GraphicsContext::resize(const uint32_t width, const uint32_t height)
	{
		_swapChain->Resize(width, height);
	}

	Diligent::RefCntAutoPtr<Diligent::IRenderDevice> GraphicsContext::getRenderDevice() const noexcept
	{
		return _device;
	}

	Diligent::RefCntAutoPtr<Diligent::IDeviceContext> GraphicsContext::getImmediateContext() const noexcept
	{
		return _immediateContext;
	}

	Diligent::RefCntAutoPtr<Diligent::ISwapChain> GraphicsContext::getSwapchain() const noexcept
	{
		return _swapChain;
	}

}