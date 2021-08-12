#include <cobalt/graphics/indexbuffer.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Buffer.h>

#include <cobalt/graphics/graphicscontext.hpp>

namespace cobalt
{
	IndexBuffer::IndexBuffer(const GraphicsContext& context, const void* data, const size_t size)
	{
		Diligent::BufferDesc bufferDesc;
		bufferDesc.Name = "Index Buffer";
		bufferDesc.Usage = Diligent::USAGE_IMMUTABLE;
		bufferDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
		bufferDesc.uiSizeInBytes = static_cast<uint32_t>(size);

		Diligent::BufferData bufferData;
		bufferData.pData = data;
		bufferData.DataSize = static_cast<uint32_t>(size);

		context.getRenderDevice()->CreateBuffer(bufferDesc, &bufferData, &_buffer);
	}

	Diligent::RefCntAutoPtr<Diligent::IBuffer> IndexBuffer::getBuffer() const
	{
		return _buffer;
	}
}
