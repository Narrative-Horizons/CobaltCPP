#pragma once

#include <cobalt/graphics/renderpass.hpp>

namespace cobalt
{
	class PBRPass : public RenderPass
	{
		public:
			PBRPass(const GraphicsContext& context);
			~PBRPass() override;

			void render(FrameInfo frameInfo) override;

		private:
			struct PBRPassImpl;
			PBRPassImpl* _impl;
	};
}