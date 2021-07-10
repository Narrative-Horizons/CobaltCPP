#pragma once

namespace cobalt
{
	class GraphicsContext;
	class VertexBuffer
	{
		public:
			VertexBuffer(const GraphicsContext& context, const void* data, const size_t size);
			~VertexBuffer();

		private:
			friend class VertexBufferHelper;

			struct VertexBufferImpl;
			VertexBufferImpl* _impl;
	};
}