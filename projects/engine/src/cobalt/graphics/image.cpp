#include <cobalt/graphics/image.hpp>
#include <cobalt/graphics/imagehelper.hpp>

namespace cobalt
{
	Image::Image(const std::string& filePath)
	{
		_impl = new ImageImpl();
		Diligent::RefCntAutoPtr<Diligent::IDataBlob> dataBlob;
		auto fileFmt = CreateImageFromFile(filePath.c_str(), &_impl->image, &dataBlob);
	}

	Image::~Image()
	{
		delete _impl;
		_impl = nullptr;
	}
}
