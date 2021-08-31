#include <cobalt/graphics/vertexbuffer.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Buffer.h>

#include <cobalt/graphics/graphicscontext.hpp>

namespace cobalt
{
	VertexBuffer::VertexBuffer(const UniquePtr<GraphicsContext>& context, const void* data, const size_t size)
	{
		Diligent::BufferDesc bufferDesc;
		bufferDesc.Name = "Vertex Buffer";
		bufferDesc.Usage = Diligent::USAGE_IMMUTABLE;
		bufferDesc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
		bufferDesc.uiSizeInBytes = static_cast<uint32_t>(size);

		Diligent::BufferData bufferData;
		bufferData.pData = data;
		bufferData.DataSize = static_cast<uint32_t>(size);

		context->getRenderDevice()->CreateBuffer(bufferDesc, &bufferData, &_buffer);
	}

	Diligent::RefCntAutoPtr<Diligent::IBuffer> VertexBuffer::getBuffer() const
	{
		return _buffer;
	}
}
