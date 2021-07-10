#pragma once

#include <cobalt/graphics/indexbuffer.hpp>
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Buffer.h>

#include <cobalt/macros.hpp>

namespace cobalt
{
	struct IndexBuffer::IndexBufferImpl
	{
		Diligent::RefCntAutoPtr<Diligent::IBuffer> buffer;
	};

	class IndexBufferHelper
	{
	public:
		explicit IndexBufferHelper(const IndexBuffer& indexBuffer);

		COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::IBuffer> getBuffer() const;

	private:
		const IndexBuffer& _indexBuffer;
	};
}
