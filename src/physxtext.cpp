#ifdef _MSC_VER
#include "src_include/physxtext.h"
#include <QDebug>

constexpr const char* PVD_HOST="127.0.0.1";

void PhysXText::Init()
{
    PxDefaultAllocator gAllocator;
    PxDefaultErrorCallback gErrorCallback;
    // basic stuff: memory allocator, error callback
    auto gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    // enable pvd(physics visual debugger)
    auto gPvd = PxCreatePvd(*gFoundation);
    PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
    gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);
    // create physics engine
    auto gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);
    // create a physics world
    PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
    auto gDispatcher = PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher	= gDispatcher;
    sceneDesc.filterShader	= PxDefaultSimulationFilterShader;
    auto gScene = gPhysics->createScene(sceneDesc);
    // pvd settings
    PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
    if(pvdClient)
    {
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }
    // create a static plane
    auto gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

    PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0,1,0,0), *gMaterial);
    gScene->addActor(*groundPlane);
    // create a bunch of boxes
    // 创建一些动态方块
    for (int i = 0; i < 5; ++i) {
        PxTransform transform(PxVec3(i * 2.0f, 5.0f, 0.0f)); // 初始位置
        PxRigidDynamic* dynamicBox = PxCreateDynamic(*gPhysics, transform, PxBoxGeometry(1.0f, 1.0f, 1.0f), *gMaterial, 1.0f);
        gScene->addActor(*dynamicBox);
    }

    // 模拟物理效果
    for (int i = 0; i < 300; ++i) {
        gScene->simulate(1.0f / 60.0f); // 模拟60帧每秒
        gScene->fetchResults(true);

        // 处理每个动态方块的位置
        for (PxU32 j = 0; j < gScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC); ++j) {
            PxRigidDynamic* actor = nullptr;
            gScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC, (PxActor**)&actor, 1, j);
            PxTransform actorTransform = actor->getGlobalPose();
            PxVec3 position = actorTransform.p;
            qDebug()<< "Frame " << i << ", Box " << j << ": Position - (" << position.x << ", " << position.y << ", " << position.z << ")\n";
        }
    }

    // 清理资源
    groundPlane->release();
    gScene->release();
    gPhysics->release();
    gFoundation->release();
}
#endif
