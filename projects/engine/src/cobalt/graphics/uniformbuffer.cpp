#include <cobalt/graphics/uniformbuffer.hpp>

#include <DiligentCore/Graphics/GraphicsTools/interface/MapHelper.hpp>

namespace cobalt
{
	UniformBuffer::UniformBuffer(const GraphicsContext& context, ShaderResourceType type, const size_t size, const std::string& name) : ShaderResource(), _context(context)
	{
		_size = size;
		
		Diligent::BufferDesc ubDesc;
		ubDesc.Name = name.c_str();
		ubDesc.uiSizeInBytes = static_cast<uint32_t>(size);
		ubDesc.Usage = Diligent::USAGE_DYNAMIC;
		ubDesc.BindFlags = Diligent::BIND_UNIFORM_BUFFER;
		ubDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;

		context.getRenderDevice()->CreateBuffer(ubDesc, nullptr, &_buffer);

		_objectData = _buffer;
	}

	void UniformBuffer::setData(const void* data, ResourceStateTransitionMode transitionMode)
	{
		void* mappedData = nullptr;
		_context.getImmediateContext()->MapBuffer(_buffer, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD, mappedData);
		memcpy(mappedData, data, _size);
		_context.getImmediateContext()->UnmapBuffer(_buffer, Diligent::MAP_WRITE);

		/*contextHelper.getImmediateContext()->UpdateBuffer(_uimpl->buffer, 0, static_cast<uint32_t>(_uimpl->size), data,
			static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));*/
	}
}
