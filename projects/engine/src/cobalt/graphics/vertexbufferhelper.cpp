#include "vertexbufferhelper.hpp"

namespace cobalt
{
	VertexBufferHelper::VertexBufferHelper(const VertexBuffer& vertexBuffer) : _vertexBuffer(vertexBuffer) { }

	Diligent::RefCntAutoPtr<Diligent::IBuffer> VertexBufferHelper::getBuffer() const
	{
		return _vertexBuffer._impl->buffer;
	}
}
