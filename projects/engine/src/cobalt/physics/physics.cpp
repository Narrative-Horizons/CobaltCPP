#include <cobalt/physics/physics.hpp>
#include <cobalt/physics/physicshelper.hpp>

#include <iostream>

namespace cobalt
{
	Physics::Physics()
	{
		_impl = new PhysicsImpl();

		using namespace physx;

		static PxDefaultErrorCallback defaultErrorCallback;
		static PxDefaultAllocator defaultAllocatorCallback;

		_impl->foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback,
			defaultErrorCallback);

		if (_impl->foundation == nullptr)
		{
			std::cerr << "PxCreateFoundation failed!" << std::endl;
			return;
		}

		_impl->pvd = PxCreatePvd(*_impl->foundation);
		_impl->transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);

		_impl->pvd->connect(*_impl->transport, PxPvdInstrumentationFlag::eALL);

		_impl->physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_impl->foundation, PxTolerancesScale(), false, _impl->pvd);
		if (_impl->physics == nullptr)
		{
			std::cerr << "PxCreatePhysics failed!" << std::endl;
			return;
		}

		_impl->cooking = PxCreateCooking(PX_PHYSICS_VERSION, *_impl->foundation, PxCookingParams(PxTolerancesScale()));
		if (_impl->cooking == nullptr)
		{
			std::cerr << "PxCreateCooking failed!" << std::endl;
			return;
		}

		if (!PxInitExtensions(*_impl->physics, _impl->pvd))
		{
			std::cerr << "PxInitExtensions failed!" << std::endl;
		}
	}

	Physics::~Physics()
	{
		PxCloseExtensions();

		delete _impl;
		_impl = nullptr;
	}
}