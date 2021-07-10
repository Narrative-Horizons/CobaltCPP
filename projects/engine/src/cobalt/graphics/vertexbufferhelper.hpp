#pragma once

#include <cobalt/graphics/vertexbuffer.hpp>
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Buffer.h>

#include <cobalt/macros.hpp>

namespace cobalt
{
	struct VertexBuffer::VertexBufferImpl
	{
		Diligent::RefCntAutoPtr<Diligent::IBuffer> buffer;
	};
	
	class VertexBufferHelper
	{
		public:
			explicit VertexBufferHelper(const VertexBuffer& vertexBuffer);

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IBuffer> getBuffer() const;

		private:
			const VertexBuffer& _vertexBuffer;
	};
}
