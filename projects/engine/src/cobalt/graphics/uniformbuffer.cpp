#include <cobalt/graphics/uniformbuffer.hpp>

#include <DiligentCore/Graphics/GraphicsTools/interface/MapHelper.hpp>

namespace cobalt
{
	struct UniformBuffer::UniformBufferImpl
	{
		Diligent::RefCntAutoPtr<Diligent::IBuffer> buffer;
		const GraphicsContext& context;
		size_t size;

		explicit UniformBufferImpl(const GraphicsContext& context) : context(context), size(0)
		{
			
		}
	};
	
	UniformBuffer::UniformBuffer(const GraphicsContext& context, ShaderResourceType type, const size_t size, const std::string& name) : ShaderResource()
	{
		_uimpl = new UniformBufferImpl(context);
		_uimpl->size = size;

		Diligent::BufferDesc ubDesc;
		ubDesc.Name = name.c_str();
		ubDesc.uiSizeInBytes = static_cast<uint32_t>(size);
		ubDesc.Usage = Diligent::USAGE_DYNAMIC;
		ubDesc.BindFlags = Diligent::BIND_UNIFORM_BUFFER;
		ubDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;

		context.getRenderDevice()->CreateBuffer(ubDesc, nullptr, &_uimpl->buffer);

		_objectData = _uimpl->buffer;
	}

	UniformBuffer::~UniformBuffer()
	{
		delete _uimpl;
		_uimpl = nullptr;
	}

	void UniformBuffer::setData(const void* data, ResourceStateTransitionMode transitionMode) const
	{
		void* mappedData = nullptr;
		_uimpl->context.getImmediateContext()->MapBuffer(_uimpl->buffer, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD, mappedData);
		memcpy(mappedData, data, _uimpl->size);
		_uimpl->context.getImmediateContext()->UnmapBuffer(_uimpl->buffer, Diligent::MAP_WRITE);

		/*contextHelper.getImmediateContext()->UpdateBuffer(_uimpl->buffer, 0, static_cast<uint32_t>(_uimpl->size), data,
			static_cast<Diligent::RESOURCE_STATE_TRANSITION_MODE>(transitionMode));*/
	}
}
