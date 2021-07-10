#pragma once

namespace cobalt
{
	class GraphicsContext;
	class IndexBuffer
	{
		public:
			IndexBuffer(const GraphicsContext& context, const void* data, const size_t size);
			~IndexBuffer();

		private:
			friend class IndexBufferHelper;

			struct IndexBufferImpl;
			IndexBufferImpl* _impl;
	};
}