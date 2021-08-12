#include <cobalt/graphics/image.hpp>

namespace cobalt
{
	Image::Image(const std::string& filePath)
	{
		Diligent::RefCntAutoPtr<Diligent::IDataBlob> dataBlob;
		auto fileFmt = CreateImageFromFile(filePath.c_str(), &_image, &dataBlob);
	}

	Image::~Image()
	{
	}

	Diligent::RefCntAutoPtr<Diligent::Image> Image::getImage() const
	{
		return _image;
	}
}
