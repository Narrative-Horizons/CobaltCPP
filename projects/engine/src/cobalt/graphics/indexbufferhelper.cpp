#include "indexbufferhelper.hpp"

namespace cobalt
{
	IndexBufferHelper::IndexBufferHelper(const IndexBuffer& vertexBuffer) : _indexBuffer(vertexBuffer) { }

	Diligent::RefCntAutoPtr<Diligent::IBuffer> IndexBufferHelper::getBuffer() const
	{
		return _indexBuffer._impl->buffer;
	}
}
