#include <cobalt/graphics/shaderstoragebuffer.hpp>

#include <DiligentCore/Graphics/GraphicsTools/interface/MapHelper.hpp>

namespace cobalt
{
	ShaderStorageBuffer::ShaderStorageBuffer(const GraphicsContext& context, ShaderResourceType type, const size_t size, const std::string& name) : ShaderResource(), _context(context)
	{
		_size = size;
		
		Diligent::BufferDesc ubDesc;
		ubDesc.Name = name.c_str();
		ubDesc.uiSizeInBytes = static_cast<uint32_t>(size); // TODO: * this the amount of structs inside the buffer
		ubDesc.Usage = Diligent::USAGE_DYNAMIC;
		ubDesc.BindFlags = Diligent::BIND_SHADER_RESOURCE;
		ubDesc.Mode = Diligent::BUFFER_MODE_STRUCTURED;
		ubDesc.ElementByteStride = static_cast<uint32_t>(size);
		ubDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;

		context.getRenderDevice()->CreateBuffer(ubDesc, nullptr, &_buffer);

		_objectData = _buffer->GetDefaultView(Diligent::BUFFER_VIEW_SHADER_RESOURCE);
	}

	void ShaderStorageBuffer::setData(const void* data, ResourceStateTransitionMode transitionMode)
	{
		void* mappedData = nullptr;
		_context.getImmediateContext()->MapBuffer(_buffer, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD, mappedData);
		memcpy(mappedData, data, _size);
		_context.getImmediateContext()->UnmapBuffer(_buffer, Diligent::MAP_WRITE);

		/*contextHelper.getImmediateContext()->UpdateBuffer(_uimpl->buffer, 0, static_cast<uint32_t>(_uimpl->size), data,
			static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));*/
	}
}
