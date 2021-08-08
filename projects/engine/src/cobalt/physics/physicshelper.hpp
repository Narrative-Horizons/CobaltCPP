#pragma once

#include <cobalt/physics/physics.hpp>
#include <cobalt/macros.hpp>

#include <PxPhysicsAPI.h>

namespace cobalt
{
	struct Physics::PhysicsImpl
	{
		physx::PxFoundation* foundation;
		physx::PxPvd* pvd;
		physx::PxPvdTransport* transport;
		physx::PxPhysics* physics;
		physx::PxCooking* cooking;

		~PhysicsImpl()
		{
			cooking->release();
			cooking = nullptr;

			transport->release();
			transport = nullptr;

			physics->release();
			physics = nullptr;

			pvd->disconnect();
			pvd->release();
			pvd = nullptr;

			foundation->release();
			foundation = nullptr;
		}
	};

	class PhysicsHelper
	{
		public:
			explicit PhysicsHelper(const Physics& physics);

			COBALT_NO_DISCARD physx::PxFoundation* getPhysXFoundation() const;
			COBALT_NO_DISCARD physx::PxPvd* getPhysXPvD() const;
			COBALT_NO_DISCARD physx::PxPvdTransport* getPhysXPvDTransport() const;
			COBALT_NO_DISCARD physx::PxPhysics* getPhysX() const;
			COBALT_NO_DISCARD physx::PxCooking* getPhysXCooking() const;

		private:
			const Physics& _physics;
	};
}