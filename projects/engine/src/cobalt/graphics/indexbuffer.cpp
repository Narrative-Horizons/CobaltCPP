#include <cobalt/graphics/indexbuffer.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Buffer.h>

#include <cobalt/graphics/graphicscontext.hpp>
#include <cobalt/graphics/graphicscontexthelper.hpp>
#include <cobalt/graphics/indexbufferhelper.hpp>

namespace cobalt
{
	IndexBuffer::IndexBuffer(const GraphicsContext& context, const void* data, const size_t size)
	{
		_impl = new IndexBufferImpl();

		Diligent::BufferDesc bufferDesc;
		bufferDesc.Name = "Index Buffer";
		bufferDesc.Usage = Diligent::USAGE_IMMUTABLE;
		bufferDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
		bufferDesc.uiSizeInBytes = static_cast<uint32_t>(size);

		Diligent::BufferData bufferData;
		bufferData.pData = data;
		bufferData.DataSize = static_cast<uint32_t>(size);

		GraphicsContextHelper* contextHelper = new GraphicsContextHelper(context);
		contextHelper->getRenderDevice()->CreateBuffer(bufferDesc, &bufferData, &_impl->buffer);
	}

	IndexBuffer::~IndexBuffer()
	{
		delete _impl;
		_impl = nullptr;
	}
}
