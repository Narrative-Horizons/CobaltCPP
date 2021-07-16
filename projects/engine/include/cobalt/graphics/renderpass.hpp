#pragma once

#include <cobalt/graphics/framebuffer.hpp>
#include <cobalt/graphics/graphicscontext.hpp>

namespace cobalt
{
	struct FrameInfo
	{
		const UniquePtr<Framebuffer>& frameBuffer;
		uint32_t width;
		uint32_t height;

		FrameInfo(const UniquePtr<Framebuffer>& frameBuffer, uint32_t width, uint32_t height) : frameBuffer(frameBuffer), width(width), height(height) {}
	};
	
	class RenderPass
	{
		public:
			RenderPass(const GraphicsContext& context, const std::string& name);
			virtual ~RenderPass() = default;

			virtual void render(FrameInfo frameInfo) = 0;

		protected:
			const GraphicsContext& _context;
			std::string _name;
	};
}