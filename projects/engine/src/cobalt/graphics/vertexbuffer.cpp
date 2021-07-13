#include <cobalt/graphics/vertexbuffer.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Buffer.h>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/graphicscontexthelper.hpp>
#include <cobalt/graphics/vertexbufferhelper.hpp>

namespace cobalt
{
	VertexBuffer::VertexBuffer(const GraphicsContext& context, const void* data, const size_t size)
	{
		_impl = new VertexBufferImpl();
		
		Diligent::BufferDesc bufferDesc;
		bufferDesc.Name = "Vertex Buffer";
		bufferDesc.Usage = Diligent::USAGE_IMMUTABLE;
		bufferDesc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
		bufferDesc.uiSizeInBytes = static_cast<uint32_t>(size);

		Diligent::BufferData bufferData;
		bufferData.pData = data;
		bufferData.DataSize = static_cast<uint32_t>(size);

		const GraphicsContextHelper contextHelper(context);
		contextHelper.getRenderDevice()->CreateBuffer(bufferDesc, &bufferData, &_impl->buffer);
	}

	VertexBuffer::~VertexBuffer()
	{
		delete _impl;
		_impl = nullptr;
	}
}
