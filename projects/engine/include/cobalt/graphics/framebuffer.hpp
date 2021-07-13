#pragma once

#include <cstdint>
#include <vector>

#include <cobalt/graphics/graphicsenums.hpp>

namespace cobalt
{
	struct FramebufferCreateInfo
	{
		uint32_t framesInFlight;

		std::vector<TextureFormat> renderTargets;
		TextureFormat depthTarget;
	};
	
	class Framebuffer
	{
		public:
			explicit Framebuffer(const FramebufferCreateInfo& createInfo);
			~Framebuffer();

			COBALT_NO_DISCARD FramebufferCreateInfo getInfo() const;

		private:
			friend class FramebufferHelper;

			struct FramebufferImpl;
			FramebufferImpl* _impl;

			FramebufferCreateInfo _createInfo;
	};
}
