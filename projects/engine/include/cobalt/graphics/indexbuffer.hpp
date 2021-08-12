#pragma once
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Buffer.h>

#include "cobalt/macros.hpp"

namespace cobalt
{
	class GraphicsContext;
	class IndexBuffer
	{
		public:
			IndexBuffer(const GraphicsContext& context, const void* data, const size_t size);
			~IndexBuffer() = default;

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IBuffer> getBuffer() const;

		private:
			Diligent::RefCntAutoPtr<Diligent::IBuffer> _buffer;
	};
}
