#pragma once

#include <cstdint>
#include <vector>

#include <cobalt/containers/smartpointers.hpp>
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
			explicit Framebuffer(const UniquePtr<GraphicsContext>& context, const FramebufferCreateInfo& createInfo);

			COBALT_NO_DISCARD FramebufferCreateInfo getInfo() const;

			void resize(uint32_t width, uint32_t height);

		private:
			FramebufferCreateInfo _createInfo;

			const UniquePtr<GraphicsContext>& _context;
	};
}
