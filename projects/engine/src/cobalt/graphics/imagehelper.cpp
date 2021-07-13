#include <cobalt/graphics/imagehelper.hpp>

namespace cobalt
{
	ImageHelper::ImageHelper(const Image& image) : _image(image) { }

	Diligent::RefCntAutoPtr<Diligent::Image> ImageHelper::getImage() const
	{
		return _image._impl->image;
	}

}