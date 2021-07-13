#include <cobalt/graphics/shaderstoragebuffer.hpp>

#include <DiligentCore/Graphics/GraphicsTools/interface/MapHelper.hpp>
#include <cobalt/graphics/graphicscontexthelper.hpp>

#include "shaderhelper.hpp"

namespace cobalt
{
	struct ShaderStorageBuffer::ShaderStorageBufferImpl
	{
		Diligent::RefCntAutoPtr<Diligent::IBuffer> buffer;
		const GraphicsContext& context;
		size_t size;

		explicit ShaderStorageBufferImpl(const GraphicsContext& context) : context(context), size(0)
		{

		}
	};

	ShaderStorageBuffer::ShaderStorageBuffer(const GraphicsContext& context, ShaderResourceType type, const size_t size, const std::string& name) : ShaderResource()
	{
		_uimpl = new ShaderStorageBufferImpl(context);
		_uimpl->size = size;
		const GraphicsContextHelper contextHelper(context);

		Diligent::BufferDesc ubDesc;
		ubDesc.Name = name.c_str();
		ubDesc.uiSizeInBytes = static_cast<uint32_t>(size); // TODO: * this the amount of structs inside the buffer
		ubDesc.Usage = Diligent::USAGE_DYNAMIC;
		ubDesc.BindFlags = Diligent::BIND_SHADER_RESOURCE;
		ubDesc.Mode = Diligent::BUFFER_MODE_STRUCTURED;
		ubDesc.ElementByteStride = static_cast<uint32_t>(size);
		ubDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;

		contextHelper.getRenderDevice()->CreateBuffer(ubDesc, nullptr, &_uimpl->buffer);

		_impl->objectData = _uimpl->buffer->GetDefaultView(Diligent::BUFFER_VIEW_SHADER_RESOURCE);
	}

	void ShaderStorageBuffer::setData(const void* data, ResourceStateTransitionMode transitionMode) const
	{
		const GraphicsContextHelper contextHelper(_uimpl->context);
		void* mappedData = nullptr;
		contextHelper.getImmediateContext()->MapBuffer(_uimpl->buffer, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD, mappedData);
		memcpy(mappedData, data, _uimpl->size);
		contextHelper.getImmediateContext()->UnmapBuffer(_uimpl->buffer, Diligent::MAP_WRITE);

		/*contextHelper.getImmediateContext()->UpdateBuffer(_uimpl->buffer, 0, static_cast<uint32_t>(_uimpl->size), data,
			static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));*/
	}
}
