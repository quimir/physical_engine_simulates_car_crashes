#include "src_include/physxtext.h"
#include <QDebug>

void PhysXText::Init()
{
    // 初始化 PhysX SDK
    PxPhysics* physics = nullptr;
    PxDefaultAllocator allocator;
    PxDefaultErrorCallback errorCallback;
    PxFoundation* foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);
    physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true);

    // 创建物理场景
    PxSceneDesc sceneDesc(physics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
    PxScene* scene = physics->createScene(sceneDesc);

    // 创建一个动态物体（球体）
    PxMaterial* material = physics->createMaterial(0.5f, 0.5f, 0.6f); // 摩擦力和弹性
    PxTransform transform(PxVec3(0.0f, 10.0f, 0.0f)); // 初始位置
    PxRigidDynamic* dynamicActor = PxCreateDynamic(*physics, transform, PxSphereGeometry(1.0f), *material, 1.0f);
    scene->addActor(*dynamicActor);

    // 模拟物理世界
    float timeStep = 1.0f / 60.0f; // 模拟时间步长
    for (int i = 0; i < 300; ++i) {
        scene->simulate(timeStep);
        scene->fetchResults(true);

        // 获取并输出物体的位置
        PxTransform pose = dynamicActor->getGlobalPose();
        qDebug() << "Time: " << i * timeStep << ", Position: " << pose.p.x << ", " << pose.p.y << ", " << pose.p.z << "\n";
    }

    // 清理资源
    dynamicActor->release();
    scene->release();
    physics->release();
    foundation->release();
}
