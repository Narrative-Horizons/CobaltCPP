#pragma once

#include <cobalt/macros.hpp>

namespace cobalt
{
	class BaseApplication
	{
		public:
			COBALT_NO_COPY_MOVE(BaseApplication)

			BaseApplication() = default;
			virtual ~BaseApplication() = default;

		
			virtual void initialize() = 0;
			virtual void update() = 0;
			virtual void render() = 0;
			virtual void cleanup() = 0;
	};
}