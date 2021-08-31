#pragma once

#include <cobalt/graphics/renderpass.hpp>

namespace cobalt
{
	class ScreenResolvePass : public RenderPass
	{
		public:
			explicit ScreenResolvePass(const UniquePtr<GraphicsContext>& context);
			~ScreenResolvePass() override = default;

			void setInputTexture(UniquePtr<Framebuffer> buffer, uint32_t index);
			void render(FrameInfo frameInfo) override;

		private:
			UniquePtr<VertexBuffer> _vertexBuffer;
			UniquePtr<IndexBuffer> _indexBuffer;
			std::vector<VertexBuffer*> _screenBuffers;
			UniquePtr<Shader> _resolveShader;

			Framebuffer* _sourceBuffer;
			uint32_t _sourceIndex;
	};
}
