#pragma once

#include <memory>
#include <cobalt/window.hpp>

#include <cobalt/graphics/graphicsenums.hpp>
#include <cobalt/graphics/framebuffer.hpp>
#include <cobalt/graphics/vertexbuffer.hpp>
#include <cobalt/graphics/indexbuffer.hpp>

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

			void setRenderTarget(const std::unique_ptr<Framebuffer>& framebuffer, ResourceStateTransitionMode transitionMode) const;
			void clearRenderTarget(const std::unique_ptr<Framebuffer>& framebuffer, uint32_t index, const float* rgba, ResourceStateTransitionMode transitionMode) const;
			void clearDepthStencil(const std::unique_ptr<Framebuffer>& framebuffer, ClearDepthStencilFlags flags, float depth, uint8_t stencil, ResourceStateTransitionMode transitionMode) const;

			void setPipelineState(Shader& shader) const;
			void commitShaderResources(Shader& shader, ResourceStateTransitionMode transitionMode) const;
		
			void setVertexBuffers(uint32_t start, const std::vector<VertexBuffer*>& buffers, uint32_t* offsets, 
									ResourceStateTransitionMode transitionMode, SetVertexBufferFlags flags) const;
			void setIndexBuffer(IndexBuffer& buffer, uint32_t byteOffset, ResourceStateTransitionMode transitionMode) const;

			void drawIndexed(const DrawIndexedAttributes& attribs) const;

			void present() const;

			void resize(uint32_t width, uint32_t height) const;

		private:
			friend class GraphicsContextHelper;

			struct GraphicsContextImpl;
			GraphicsContextImpl* _impl;
	};
}
