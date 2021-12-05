#pragma once

#include <cobalt/containers/smartpointers.hpp>

#include <cobalt/graphics/graphicscontext.hpp>

namespace cobalt
{
	class UniformBuffer
	{
		public:

		private:
			const UniquePtr<GraphicsContext>& _context;
			size_t _size;
	};
}