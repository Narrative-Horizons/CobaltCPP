#pragma once

#include <cstdint>
#include <vector>

#include <cobalt/graphics/graphicsenums.hpp>

namespace cobalt
{
	class GraphicsContext;
	
	struct FramebufferCreateInfo
	{
		uint32_t framesInFlight;

		std::vector<TextureFormat> renderTargets;
		TextureFormat depthTarget;

		uint32_t width;
		uint32_t height;
	};
	
	class Framebuffer
	{
		public:
			explicit Framebuffer(const GraphicsContext& context, const FramebufferCreateInfo& createInfo);
			~Framebuffer();

			COBALT_NO_DISCARD FramebufferCreateInfo getInfo() const;

			void resize(uint32_t width, uint32_t height);

		private:
			friend class FramebufferHelper;

			struct FramebufferImpl;
			FramebufferImpl* _impl;

			FramebufferCreateInfo _createInfo;

			const GraphicsContext& _context;
	};
}
