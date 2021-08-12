#pragma once

#include <cobalt/graphics/renderpass.hpp>

namespace cobalt
{
	class ScreenResolvePass : public RenderPass
	{
		public:
			ScreenResolvePass(GraphicsContext& context);
			~ScreenResolvePass() override;

			void setInputTexture(UniquePtr<Framebuffer> buffer, uint32_t index) const;
			void render(FrameInfo frameInfo) override;

		private:
			struct ScreenResolvePassImpl;
			ScreenResolvePassImpl* _impl;
	};
}
