#pragma once

#include <cobalt/graphics/image.hpp>
#include <cobalt/macros.hpp>

#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentTools/TextureLoader/interface/Image.h>

namespace cobalt
{
	struct Image::ImageImpl
	{
		Diligent::RefCntAutoPtr<Diligent::Image> image;
	};

	class ImageHelper
	{
		public:
			explicit ImageHelper(const Image& image);

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::Image> getImage() const;

		private:
			const Image& _image;
	};
}
