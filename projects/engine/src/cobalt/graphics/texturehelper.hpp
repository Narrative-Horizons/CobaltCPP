#pragma once

#include <cobalt/graphics/texture.hpp>
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentCore/Graphics/GraphicsEngine/interface/Texture.h>

namespace cobalt
{
	struct Texture::TextureImpl
	{
		Diligent::RefCntAutoPtr<Diligent::ITexture> texture;
	};

	class TextureHelper
	{
		public:
			explicit TextureHelper(const Texture& texture);

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::ITexture> getTexture() const;

		private:
			const Texture& _texture;
	};
}
