#pragma once

#include <string>

namespace cobalt
{
	class Image
	{
		public:
			Image(const std::string& filePath);
			~Image();
		
		private:
			friend class ImageHelper;
		
			struct ImageImpl;
			ImageImpl* _impl;
	};
}
