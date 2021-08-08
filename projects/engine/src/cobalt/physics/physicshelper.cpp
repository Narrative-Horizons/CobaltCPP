#include <cobalt/physics/physicshelper.hpp>

namespace cobalt
{
	PhysicsHelper::PhysicsHelper(const Physics& physics) : _physics(physics) { }

	physx::PxFoundation* PhysicsHelper::getPhysXFoundation() const
	{
		return _physics._impl->foundation;
	}

	physx::PxPvd* PhysicsHelper::getPhysXPvD() const
	{
		return _physics._impl->pvd;
	}

	physx::PxPvdTransport* PhysicsHelper::getPhysXPvDTransport() const
	{
		return _physics._impl->transport;
	}

	physx::PxPhysics* PhysicsHelper::getPhysX() const
	{
		return _physics._impl->physics;
	}

	physx::PxCooking* PhysicsHelper::getPhysXCooking() const
	{
		return _physics._impl->cooking;
	}
}