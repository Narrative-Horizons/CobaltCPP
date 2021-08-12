#pragma once

#include <memory>
#include <cobalt/window.hpp>

#include <cobalt/graphics/graphicsenums.hpp>
#include <cobalt/graphics/framebuffer.hpp>
#include <cobalt/graphics/vertexbuffer.hpp>
#include <cobalt/graphics/indexbuffer.hpp>

#include <cobalt/containers/smartpointers.hpp>

#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h>
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentTools/Imgui/interface/ImGuiDiligentRenderer.hpp>
#include <DiligentTools/ThirdParty/imgui/imgui.h>

namespace cobalt
{
	class Shader;
	enum class GraphicsAPI
	{
		Vulkan,
		OpenGL,
		DX11,
		DX12
	};

	struct GraphicsContextCreateInfo
	{
		GraphicsAPI api;
	};

	struct DrawIndexedAttributes
	{
		uint32_t numIndices = 0;
		ValueType indexType = ValueType::UNDEFINED;
		DrawFlags flags = DrawFlags::NONE;
		uint32_t numInstances = 1;
		uint32_t firstIndexLocation = 0;
		uint32_t baseVertex = 0;
		uint32_t firstInstanceLocation = 0;
	};

	class GraphicsContext
	{
		public:
			GraphicsContext(const Window& window, GraphicsContextCreateInfo createInfo);
			~GraphicsContext();

			COBALT_NO_COPY(GraphicsContext)

			GraphicsContext(GraphicsContext&& other) noexcept;
			GraphicsContext& operator=(GraphicsContext&& other) noexcept;

			void setRenderTarget(const UniquePtr<Framebuffer>& framebuffer, ResourceStateTransitionMode transitionMode);
			void clearRenderTarget(const UniquePtr<Framebuffer>& framebuffer, uint32_t index, const float* rgba, ResourceStateTransitionMode transitionMode);
			void clearDepthStencil(const UniquePtr<Framebuffer>& framebuffer, ClearDepthStencilFlags flags, float depth, uint8_t stencil, ResourceStateTransitionMode transitionMode);

			void setPipelineState(Shader& shader);
			void commitShaderResources(Shader& shader, ResourceStateTransitionMode transitionMode);
		
			void setVertexBuffers(uint32_t start, const std::vector<VertexBuffer*>& buffers, uint32_t* offsets, 
									ResourceStateTransitionMode transitionMode, SetVertexBufferFlags flags);
			void setIndexBuffer(IndexBuffer& buffer, uint32_t byteOffset, ResourceStateTransitionMode transitionMode);

			void drawIndexed(const DrawIndexedAttributes& attribs);

			void present();

			void resize(uint32_t width, uint32_t height);

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IRenderDevice> getRenderDevice() const noexcept;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IDeviceContext> getImmediateContext() const noexcept;
			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::ISwapChain> getSwapchain() const noexcept;

		private:
			Diligent::RefCntAutoPtr<Diligent::IRenderDevice> _device;
			Diligent::RefCntAutoPtr<Diligent::IDeviceContext> _immediateContext;
			Diligent::RefCntAutoPtr<Diligent::ISwapChain> _swapChain;
			Diligent::RENDER_DEVICE_TYPE _deviceType = Diligent::RENDER_DEVICE_TYPE_D3D11;
			Diligent::ImGuiDiligentRenderer* _guiRenderer;
			ImGuiContext* _guiContext;

			const Window* _window;
	};
}
