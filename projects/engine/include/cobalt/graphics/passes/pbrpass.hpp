#pragma once

#include <cobalt/graphics/renderpass.hpp>

namespace cobalt
{
	class PBRPass : public RenderPass
	{
		public:
			explicit PBRPass(GraphicsContext& context);
			~PBRPass() override = default;

			void render(FrameInfo frameInfo) override;

		private:
			UniquePtr<Shader> _pbrShader;
			UniquePtr<Shader> _pbrTranslucentShader;
	};
}