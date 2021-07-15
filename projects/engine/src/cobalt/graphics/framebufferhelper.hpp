#pragma once

#include <vector>
#include <cobalt/graphics/framebuffer.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/TextureView.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Texture.h>

#include <cobalt/macros.hpp>

namespace cobalt
{
	struct Framebuffer::FramebufferImpl
	{
		std::vector<Diligent::RefCntAutoPtr<Diligent::ITexture>> renderTargets;
		Diligent::RefCntAutoPtr<Diligent::ITexture> depthTarget;
	};

	class FramebufferHelper
	{
		public:
			explicit FramebufferHelper(const Framebuffer& framebuffer);

			COBALT_NO_DISCARD Diligent::ITexture** getRenderTargets() const;
			COBALT_NO_DISCARD Diligent::ITextureView* getRenderTarget(uint32_t index, TextureTypeView viewType) const;
			COBALT_NO_DISCARD Diligent::ITextureView* getDepthTarget(TextureTypeView viewType) const;

		private:
			const Framebuffer& _framebuffer;
	};
}
