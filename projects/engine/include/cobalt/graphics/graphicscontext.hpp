#pragma once

#include <cobalt/window.hpp>

#include <cobalt/graphics/graphicsenums.hpp>
#include <cobalt/graphics/framebuffer.hpp>

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

	class GraphicsContext
	{
		public:
			GraphicsContext(const Window& window, GraphicsContextCreateInfo createInfo);
			~GraphicsContext();

			COBALT_NO_COPY(GraphicsContext)

			GraphicsContext(GraphicsContext&& other) noexcept;
			GraphicsContext& operator=(GraphicsContext&& other) noexcept;

			void setRenderTarget(Framebuffer& framebuffer, ResourceStateTransitionMode transitionMode) const;
			void clearRenderTarget();
			void clearDepthStencil();

			void setPipelineState(Shader& shader);

			void present() const;

			void resize(uint32_t width, uint32_t height) const;

		private:
			friend class GraphicsContextHelper;

			struct GraphicsContextImpl;
			GraphicsContextImpl* _impl;
	};
}
