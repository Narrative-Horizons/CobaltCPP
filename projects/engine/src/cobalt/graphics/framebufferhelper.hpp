#pragma once

#include <vector>
#include <cobalt/graphics/framebuffer.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/TextureView.h>

#include <cobalt/macros.hpp>

namespace cobalt
{
	struct Framebuffer::FramebufferImpl
	{
		std::vector<std::vector<Diligent::RefCntAutoPtr<Diligent::ITextureView>>> renderTargets;
		std::vector < Diligent::RefCntAutoPtr<Diligent::ITextureView>> depthTarget;
	};

	class FramebufferHelper
	{
		public:
			explicit FramebufferHelper(const Framebuffer& framebuffer);

			COBALT_NO_DISCARD Diligent::ITextureView** getRenderTargets(uint32_t frame) const;
			COBALT_NO_DISCARD Diligent::ITextureView* getRenderTarget(uint32_t frame, uint32_t index) const;
			COBALT_NO_DISCARD Diligent::ITextureView* getDepthTarget(uint32_t frame) const;

		private:
			const Framebuffer& _framebuffer;
	};
}
