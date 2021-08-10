#include <cobalt/physics/physics.hpp>
#include <cobalt/physics/physicshelper.hpp>

#include <iostream>

namespace cobalt
{
	bool isCCDActive(physx::PxFilterData& filterData)
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

#if defined(PX_SUPPORT_GPU_PHYSX) && defined(_WIN32)
		const PxCudaContextManagerDesc cudaDesc;

		_impl->cudaContext = PxCreateCudaContextManager(*_impl->foundation, cudaDesc);

		if(_impl->cudaContext == nullptr)
		{
			std::cerr << "PxCreateCudaContextManager failed!" << std::endl;
		}

		if(_impl->cudaContext != nullptr && _impl->cudaContext->contextIsValid() == false)
		{
			std::cerr << "Cuda Context is invalid!" << std::endl;
		}
#endif

		const PxTolerancesScale scale;

		_impl->pvd = PxCreatePvd(*_impl->foundation);
		_impl->transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
		_impl->pvd->connect(*_impl->transport, PxPvdInstrumentationFlag::eALL);

		_impl->physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_impl->foundation, scale, true, _impl->pvd);
		if (_impl->physics == nullptr)
		{
			std::cerr << "PxCreatePhysics failed!" << std::endl;
			return;
		}

		PxCookingParams params(scale);
		params.meshWeldTolerance = 0.001f;
		params.meshPreprocessParams = PxMeshPreprocessingFlags(PxMeshPreprocessingFlag::eWELD_VERTICES);
		_impl->cooking = PxCreateCooking(PX_PHYSICS_VERSION, *_impl->foundation, params);
		if (_impl->cooking == nullptr)
		{
			std::cerr << "PxCreateCooking failed!" << std::endl;
			return;
		}

		if (!PxInitExtensions(*_impl->physics, _impl->pvd))
		{
			std::cerr << "PxInitExtensions failed!" << std::endl;
			return;
		}

		// Create the scene
		PxSceneDesc sceneDesc(scale);
		sceneDesc.gravity = PxVec3(0, -9.81f, 0);

		if(!sceneDesc.cpuDispatcher)
		{
			_impl->cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
			if(_impl->cpuDispatcher == nullptr)
			{
				std::cerr << "PxDefaultCpuDispatcherCreate failed!" << std::endl;
				return;
			}
			sceneDesc.cpuDispatcher = _impl->cpuDispatcher;
		}

#if defined(PX_SUPPORT_GPU_PHYSX) && defined(_WIN32)
		// Set GPU dispatcher
#endif

		sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
		sceneDesc.filterShader = gameCollisionFilterShader;

		_impl->scene = _impl->physics->createScene(sceneDesc);
		//_impl->scene->setSimulationEventCallback() TODO
		_impl->scene->simulate(0.02f); // Prewarm
	}
	
	Physics::~Physics()
	{
		PxCloseExtensions();

		delete _impl;
		_impl = nullptr;
	}
}