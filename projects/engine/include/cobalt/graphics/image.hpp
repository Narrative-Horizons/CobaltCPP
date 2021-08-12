#pragma once

#include <string>
#include <DiligentCore/Common/interface/RefCntAutoPtr.hpp>
#include <DiligentTools/TextureLoader/interface/Image.h>

#include "cobalt/macros.hpp"

namespace cobalt
{
	class Image
	{
		public:
			explicit Image(const std::string& filePath);
			~Image();

			COBALT_NO_DISCARD Diligent::RefCntAutoPtr<Diligent::Image> getImage() const;
		
		private:
			Diligent::RefCntAutoPtr<Diligent::Image> _image;
	};
}
