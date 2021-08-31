#pragma once

#include <cstdint>
#include <vector>

#include <cobalt/containers/smartpointers.hpp>

#include <cobalt/graphics/graphicsenums.hpp>
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Texture.h>

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

			COBALT_NO_DISCARD Diligent::ITexture** getRenderTargets();
			COBALT_NO_DISCARD Diligent::ITextureView* getRenderTarget(uint32_t index, TextureTypeView viewType);
			COBALT_NO_DISCARD Diligent::ITextureView* getDepthTarget(TextureTypeView viewType);

			void resize(uint32_t width, uint32_t height);

		private:
			FramebufferCreateInfo _createInfo;

			const UniquePtr<GraphicsContext>& _context;

			std::vector<Diligent::RefCntAutoPtr<Diligent::ITexture>> _renderTargets;
			Diligent::RefCntAutoPtr<Diligent::ITexture> _depthTarget;
	};
}
