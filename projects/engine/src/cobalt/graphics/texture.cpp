#include <cobalt/graphics/texture.hpp>
#include <cobalt/graphics/texturehelper.hpp>

#include <DiligentTools/TextureLoader/interface/TextureLoader.h>

namespace cobalt
{
	Texture::Texture(const GraphicsContext& context, const Image& image, const TextureCreateInfo& createInfo) : _image(image)
	{
		_timpl = new TextureImpl();

		Diligent::TextureLoadInfo loadInfo;
		loadInfo.BindFlags = static_cast<Diligent::BIND_FLAGS>(createInfo.bindFlags);
		loadInfo.CPUAccessFlags = static_cast<Diligent::CPU_ACCESS_FLAGS>(createInfo.accessFlags);
		loadInfo.Format = static_cast<Diligent::TEXTURE_FORMAT>(createInfo.format);
		loadInfo.GenerateMips = createInfo.generateMips;
		loadInfo.IsSRGB = createInfo.isSRGB;
		loadInfo.Name = createInfo.name.c_str();
		loadInfo.Usage = static_cast<Diligent::USAGE>(createInfo.usage);
		
		CreateTextureFromImage(image.getImage(), loadInfo, context.getRenderDevice(), &_timpl->texture);

		_objectData = _timpl->texture->GetDefaultView(Diligent::TEXTURE_VIEW_SHADER_RESOURCE);
	}

	Texture::~Texture()
	{
		delete _timpl;
		_timpl = nullptr;
	}
}
