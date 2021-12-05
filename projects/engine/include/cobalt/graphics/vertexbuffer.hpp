#pragma once

#include <cobalt/containers/smartpointers.hpp>

#include "cobalt/macros.hpp"

namespace cobalt
{
	class GraphicsContext;
	class VertexBuffer
	{
		public:
			VertexBuffer(const UniquePtr<GraphicsContext>& context, const void* data, const size_t size);
			~VertexBuffer() = default;

			COBALT_NO_COPY_MOVE(VertexBuffer)

		private:
		
	};
}
