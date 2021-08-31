#pragma once

#include <cobalt/containers/smartpointers.hpp>

#include <cobalt/graphics/renderpass.hpp>

namespace cobalt
{
	class PBRPass : public RenderPass
	{
		public:
			explicit PBRPass(const UniquePtr<GraphicsContext>& context);
			~PBRPass() override = default;

			void render(FrameInfo frameInfo) override;

		private:
			UniquePtr<Shader> _pbrShader;
			UniquePtr<Shader> _pbrTranslucentShader;
	};
}