#pragma once

#include <cobalt/containers/smartpointers.hpp>

#include "cobalt/macros.hpp"

namespace cobalt
{
	class GraphicsContext;
	class IndexBuffer
	{
		public:
			IndexBuffer(const UniquePtr<GraphicsContext>& context, const void* data, const size_t size);
			~IndexBuffer() = default;

			COBALT_NO_COPY_MOVE(IndexBuffer)

		private:
	};
}
