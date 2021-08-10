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
		physx::PxCudaContextManager* cudaContext;
		physx::PxDefaultCpuDispatcher* cpuDispatcher;
		physx::PxSimulationFilterShader* simulationFilterShader;
		physx::PxScene* scene;

		~PhysicsImpl()
		{
			scene->release();
			scene = nullptr;
			
			cpuDispatcher->release();
			cpuDispatcher = nullptr;
			
#if defined(PX_SUPPORT_GPU_PHYSX) && defined(_WIN32)
			if (cudaContext != nullptr)
			{
				cudaContext->release();
				cudaContext = nullptr;
			}
#endif
			
			physics->release();
			physics = nullptr;

			delete simulationFilterShader;
			simulationFilterShader = nullptr;
			
			cooking->release();
			cooking = nullptr;

			pvd->release();
			pvd = nullptr;

			transport->release();
			transport = nullptr;

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