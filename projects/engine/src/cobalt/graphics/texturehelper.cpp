#include <cobalt/graphics/texturehelper.hpp>

namespace cobalt
{
	TextureHelper::TextureHelper(const Texture& texture) : _texture(texture) { }

	Diligent::RefCntAutoPtr<Diligent::ITexture> TextureHelper::getTexture() const
	{
		return _texture._timpl->texture;
	}
}
