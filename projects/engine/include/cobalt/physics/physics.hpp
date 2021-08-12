#pragma once

#include <PxPhysicsAPI.h>

namespace cobalt
{
	class Physics
	{
		public:
			Physics();
			~Physics();

		private:
			physx::PxFoundation* _foundation;
			physx::PxPvd* _pvd;
			physx::PxPvdTransport* _transport;
			physx::PxPhysics* _physics;
			physx::PxCooking* _cooking;
			physx::PxCudaContextManager* _cudaContext;
			physx::PxDefaultCpuDispatcher* _cpuDispatcher;
			physx::PxSimulationFilterShader* _simulationFilterShader;
			physx::PxScene* _scene;
	};
}