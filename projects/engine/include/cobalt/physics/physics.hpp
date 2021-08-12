#pragma once

namespace cobalt
{
	class Physics
	{
		public:
			Physics();
			~Physics();

		private:
			struct PhysicsImpl;
			PhysicsImpl* _impl;
	};
}