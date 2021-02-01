#include "WallBase.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent.h>
#include <game/BuildSystem/BuildObjects/Components/VisualizerComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

const double WallBase::m_ModelSize = 112;
const double WallBase::m_Height = 112;

WallBase::WallBase(edict_t *owner)
{
    AddComponent(new OwnerComponent(owner));

    auto visualizer = new VisualizerComponent(0.3);
    visualizer->Enable();

    AddComponent(visualizer);

    auto stability = new StabilityComponent();
    AddComponent(stability);
}

void WallBase::Start()
{
    GameObject::Start();
}

void WallBase::Update()
{
    GameObject::Update();

    if (m_State != BuildState::STATE_SOLID)
    {
        AimPointHandler();
    }
}

void WallBase::StateUpdated()
{
    GameObject::StateUpdated();

    // Update Connections

    if (GetState() != BuildState::STATE_SOLID)
        return;

    auto objects = ObjectManager::Instance().GetObjectsInArea(
        *GetTransform()->GetPosition());

    for (auto object : objects)
    {
        if (object.empty() || object.expired())
            continue;

        auto foundation = dynamic_cast<WallBase *>(*object.lock());

        if (foundation == nullptr)
        {
            object.reset();
            continue;
        }

        if (foundation->Id == this->Id)
            continue;

        ConnectFoundations(foundation);
    }
}

void WallBase::AimPointHandler()
{
    auto ownerComponent = GetComponent<OwnerComponent>();

    auto viewPoint = ownerComponent->GetAimDest(250.0);
    viewPoint.z += 8;

    auto aimRay = ownerComponent->GetAimRay(viewPoint, 500.0);
    auto angles = ownerComponent->GetViewAngles();

    auto aimTest = AimTest(aimRay);

    if (!aimTest.m_IsPassed)
    {
        aimTest.m_Origin = viewPoint;
        aimTest.m_Angle = angles.y;
    }

    auto interTest = IntersectionTest(aimTest);

    auto groundTest = TraceGroundTest(aimTest);

    if (interTest.m_IsPassed)
    {
        auto maxHeightTest = MaxHeightTest(aimTest, groundTest);

        if ((aimTest.m_IsPassed && !maxHeightTest.m_IsPassed) ||
            !groundTest.m_IsPassed)
            TrySetState(BuildState::STATE_CANNOT_BUILD);
        else
            TrySetState(BuildState::STATE_CAN_BUILD);

        if (groundTest.m_IsPassed && aimTest.m_IsPassed)
        {
            GetTransform()->GetPosition()->setVector(maxHeightTest.m_Origin);
            GetTransform()->GetRotation()->y(180 + maxHeightTest.m_Angle);
        }
        else if (groundTest.m_IsPassed)
        {
            GetTransform()->GetPosition()->setVector(groundTest.m_Origin);
            GetTransform()->GetRotation()->y(180 + groundTest.m_Angle);
        }
        else
        {
            GetTransform()->GetPosition()->setVector(viewPoint);
            GetTransform()->GetRotation()->y(180 + angles.y);
        }

        return;
    }
    else
    {
        TrySetState(BuildState::STATE_CANNOT_BUILD);

        GetTransform()->GetPosition()->setVector(viewPoint);
        GetTransform()->GetRotation()->y(180 + angles.y);
    }

    // if (aimTest.m_IsPassed && groundTest.m_IsPassed)
    // {
    //     if (groundTest.m_Origin.z < aimTest.m_Origin.z)
    //     {
    //         TrySetState(BuildState::STATE_CANNOT_BUILD);

    //         GetTransform()->GetPosition()->setVector(
    //             aimTest.m_Origin.x,
    //             aimTest.m_Origin.y,
    //             aimTest.m_Origin.z);

    //         GetTransform()->GetRotation()->y(180 + aimTest.m_Angle);

    //         return;
    //     }
    // }

    // TrySetState(groundTest.m_IsPassed
    //                 ? BuildState::STATE_CAN_BUILD
    //                 : BuildState::STATE_CANNOT_BUILD);

    // if (groundTest.m_IsPassed)
    // {
    //     GetTransform()->GetPosition()->setVector(
    //         groundTest.m_Origin.x,
    //         groundTest.m_Origin.y,
    //         groundTest.m_Origin.z);

    //     GetTransform()->GetRotation()->y(
    //         180 + (aimTest.m_IsPassed
    //                    ? aimTest.m_Angle
    //                    : angles.y));
    // }
    // else
    // {
    //     GetTransform()->GetPosition()->setVector(viewPoint.x, viewPoint.y, viewPoint.z);
    //     GetTransform()->GetRotation()->y(180 + angles.y);
    // }
}

AimTestResult WallBase::MaxHeightTest(AimTestResult aimTest, AimTestResult groundTest)
{
    auto isTooHigh = groundTest.m_Origin.z < aimTest.m_Origin.z;

    return AimTestResult(!isTooHigh, aimTest.m_Origin, aimTest.m_Angle);
}

AimTestResult WallBase::MinHeightTest(AimTestResult aimTest, AimTestResult groundTest)
{
    auto isTooLow = aimTest.m_Origin.z < groundTest.m_Origin.z;

    return AimTestResult(!isTooLow, aimTest.m_Origin);
}

AimTestResult WallBase::IntersectionTest(AimTestResult result)
{
    // Skip test if previous wasn't passed
    // if (!result.m_IsPassed)
    //     return result;

    auto objects = ObjectManager::Instance().GetObjectsInArea(result.m_Origin);

    auto shape = GetShape(AimTestResult(
        result.m_IsPassed,
        result.m_Origin,
        result.m_Angle + 180));

    for (auto object : objects)
    {
        if (object.empty() || object.expired())
            continue;

        auto foundation = dynamic_cast<WallBase *>(*object.lock());

        if (foundation == nullptr)
        {
            object.reset();
            continue;
        }

        if (foundation->Id == this->Id)
            continue;

        auto otherShape = foundation->GetShape();

        if (shape.IsIntersect(otherShape))
            return AimTestResult(false, result.m_Origin, result.m_Angle);
    }

    return AimTestResult(true, result.m_Origin, result.m_Angle);
}

Shape WallBase::GetShape()
{
    return GetShape(AimTestResult(
        true,
        *GetTransform()->GetPosition(),
        GetTransform()->GetRotation()->y()));
}