#include <cobalt/graphics/framebuffer.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Texture.h>

#include <cobalt/graphics/framebufferhelper.hpp>
#include <cobalt/graphics/graphicscontexthelper.hpp>
#include <cobalt/graphics/graphicscontext.hpp>

namespace cobalt
{
	Framebuffer::Framebuffer(const GraphicsContext& context, const FramebufferCreateInfo& createInfo) : _context(context)
	{
		_impl = new FramebufferImpl();
		_createInfo = createInfo;

		resize(createInfo.width, createInfo.height);
	}

	Framebuffer::~Framebuffer()
	{
		delete _impl;
		_impl = nullptr;
	}

	FramebufferCreateInfo Framebuffer::getInfo() const
	{
		return _createInfo;
	}

	void Framebuffer::resize(const uint32_t width, const uint32_t height)
	{
		_createInfo.width = width;
		_createInfo.height = height;

		const GraphicsContextHelper contextHelper(_context);
		
		for (const TextureFormat& format : _createInfo.renderTargets)
		{
			Diligent::TextureDesc desc;
			desc.Format = static_cast<Diligent::TEXTURE_FORMAT>(format);
			desc.Type = Diligent::RESOURCE_DIM_TEX_2D;
			desc.MipLevels = 1;
			desc.BindFlags = Diligent::BIND_SHADER_RESOURCE | Diligent::BIND_RENDER_TARGET;
			desc.Width = _createInfo.width;
			desc.Height = _createInfo.height;

			Diligent::RefCntAutoPtr<Diligent::ITexture> tex;

			contextHelper.getRenderDevice()->CreateTexture(desc, nullptr, &tex);
			_impl->renderTargets.push_back(tex);
		}

		if (_createInfo.depthTarget != TextureFormat::UNKNOWN)
		{
			Diligent::TextureDesc desc;
			desc.Format = static_cast<Diligent::TEXTURE_FORMAT>(_createInfo.depthTarget);
			desc.BindFlags = Diligent::BIND_SHADER_RESOURCE | Diligent::BIND_DEPTH_STENCIL;
			desc.Width = _createInfo.width;
			desc.Height = _createInfo.height;
			desc.Type = Diligent::RESOURCE_DIM_TEX_2D;
			
			contextHelper.getRenderDevice()->CreateTexture(desc, nullptr, &_impl->depthTarget);
		}
	}
}

