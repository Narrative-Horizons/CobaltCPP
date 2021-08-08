#pragma once

namespace cobalt
{
	class Physics
	{
		public:
			Physics();
			~Physics();

		private:
			friend class PhysicsHelper;

			struct PhysicsImpl;
			PhysicsImpl* _impl;
	};
}