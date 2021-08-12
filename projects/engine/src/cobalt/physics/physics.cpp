#include <cobalt/physics/physics.hpp>

#include <iostream>

#include <PxPhysicsAPI.h>

namespace cobalt
{
	bool IsCcdActive(physx::PxFilterData& filterData)
	{
		return true;
		//return filterData.word3 & CCD_FLAG ? true : false;
	}

	physx::PxFilterFlags gameCollisionFilterShader(
		const physx::PxFilterObjectAttributes aAttributes0, const physx::PxFilterData aFilterData0,
		const physx::PxFilterObjectAttributes aAttributes1, const physx::PxFilterData aFilterData1,
		physx::PxPairFlags& aPairFlags, const void* aConstantBlock, physx::PxU32 aConstantBlockSize)
	{
		// let triggers through
		if (physx::PxFilterObjectIsTrigger(aAttributes0) || physx::PxFilterObjectIsTrigger(aAttributes1))
		{
			aPairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
			return physx::PxFilterFlag::eDEFAULT;
		}

		// generate contacts for all that were not filtered above
		aPairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

		// trigger the contact callback for pairs (A,B) where
		// the filtermask of A contains the ID of B and vice versa.
		if ((aFilterData0.word0 & aFilterData1.word1) && (aFilterData1.word0 & aFilterData0.word1))
			aPairFlags |= physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;

		return physx::PxFilterFlag::eDEFAULT;

		/*PxFilterFlags filterFlags = PxDefaultSimulationFilterShader(aAttributes0,
			filterData0, aAttributes1, filterData1, pairFlags, constantBlock, constantBlockSize);

		if (isCCDActive(filterData0) && isCCDActive(filterData1))
		{
			pairFlags |= PxPairFlag::eCCD_LINEAR;
		}

		return filterFlags;*/
	}

	Physics::Physics()
	{
		using namespace physx;

		static PxDefaultErrorCallback defaultErrorCallback;
		static PxDefaultAllocator defaultAllocatorCallback;

		_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback,
			defaultErrorCallback);

		if (_foundation == nullptr)
		{
			std::cerr << "PxCreateFoundation failed!" << std::endl;
			return;
		}

#if defined(PX_SUPPORT_GPU_PHYSX) && defined(_WIN32)
		const PxCudaContextManagerDesc cudaDesc;

		_cudaContext = PxCreateCudaContextManager(*_foundation, cudaDesc);

		if(_cudaContext == nullptr)
		{
			std::cerr << "PxCreateCudaContextManager failed!" << std::endl;
		}

		if(_cudaContext != nullptr && _cudaContext->contextIsValid() == false)
		{
			std::cerr << "Cuda Context is invalid!" << std::endl;
		}
#endif

		const PxTolerancesScale scale;

		_pvd = PxCreatePvd(*_foundation);
		_transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
		_pvd->connect(*_transport, PxPvdInstrumentationFlag::eALL);

		_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, scale, true, _pvd);
		if (_physics == nullptr)
		{
			std::cerr << "PxCreatePhysics failed!" << std::endl;
			return;
		}

		PxCookingParams params(scale);
		params.meshWeldTolerance = 0.001f;
		params.meshPreprocessParams = PxMeshPreprocessingFlags(PxMeshPreprocessingFlag::eWELD_VERTICES);
		_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *_foundation, params);
		if (_cooking == nullptr)
		{
			std::cerr << "PxCreateCooking failed!" << std::endl;
			return;
		}

		if (!PxInitExtensions(*_physics, _pvd))
		{
			std::cerr << "PxInitExtensions failed!" << std::endl;
			return;
		}

		// Create the scene
		PxSceneDesc sceneDesc(scale);
		sceneDesc.gravity = PxVec3(0, -9.81f, 0);

		if(!sceneDesc.cpuDispatcher)
		{
			_cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
			if(_cpuDispatcher == nullptr)
			{
				std::cerr << "PxDefaultCpuDispatcherCreate failed!" << std::endl;
				return;
			}
			sceneDesc.cpuDispatcher = _cpuDispatcher;
		}

#if defined(PX_SUPPORT_GPU_PHYSX) && defined(_WIN32)
		// Set GPU dispatcher
#endif

		sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
		sceneDesc.filterShader = gameCollisionFilterShader;

		_scene = _physics->createScene(sceneDesc);
		//_scene->setSimulationEventCallback() TODO
		_scene->simulate(0.02f); // Prewarm
	}
	
	Physics::~Physics()
	{	
		PxCloseExtensions();
		
		_scene->release();
		_scene = nullptr;

		_cpuDispatcher->release();
		_cpuDispatcher = nullptr;

#if defined(PX_SUPPORT_GPU_PHYSX) && defined(_WIN32)
		if (_cudaContext != nullptr)
		{
			_cudaContext->release();
			_cudaContext = nullptr;
		}
#endif

		_physics->release();
		_physics = nullptr;

		_simulationFilterShader = nullptr;

		_cooking->release();
		_cooking = nullptr;

		_pvd->release();
		_pvd = nullptr;

		_transport->release();
		_transport = nullptr;

		_foundation->release();
		_foundation = nullptr;
	}
}