#pragma once

namespace cobalt
{
	class BaseApplication
	{
		public:
			virtual void initialize() = 0;
			virtual void update() = 0;
			virtual void render() = 0;
			virtual void cleanup() = 0;
	};
}