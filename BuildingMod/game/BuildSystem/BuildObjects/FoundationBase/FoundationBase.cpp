#include "FoundationBase.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent.h>
#include <game/BuildSystem/BuildObjects/Components/VisualizerComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

const double FoundationBase::m_ModelSize = 112;
const double FoundationBase::m_MinHeight = 8;
const double FoundationBase::m_MaxHeight = m_ModelSize - m_MinHeight;

FoundationBase::FoundationBase(edict_t *owner)
{
    AddComponent(new OwnerComponent(owner));

    auto visualizer = new VisualizerComponent(0.3);
    visualizer->Disable();

    AddComponent(visualizer);
}

void FoundationBase::Start()
{
    GameObject::Start();
}

void FoundationBase::Update()
{
    GameObject::Update();

    if (m_State != BuildState::STATE_SOLID)
    {
        AimPointHandler();
    }
}

void FoundationBase::StateUpdated()
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

        auto foundation = dynamic_cast<FoundationBase *>(*object.lock());

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

void FoundationBase::AimPointHandler()
{
    auto ownerComponent = GetComponent<OwnerComponent>();

    auto viewPoint = ownerComponent->GetAimDest(250.0);
    viewPoint.z += m_MinHeight;

    auto aimRay = ownerComponent->GetAimRay(viewPoint, 500.0);
    auto angles = ownerComponent->GetViewAngles();

    auto aimTest = FoundationAimTest(aimRay);

    if (!aimTest.m_IsPassed)
    {
        aimTest.m_Origin = viewPoint;
        aimTest.m_Angle = angles.y;
    }

    auto interTest = IntersectionTest(aimTest);

    auto groundTest = TraceGroundTest(aimTest);

    if (interTest.m_IsPassed && groundTest.m_IsPassed)
    {
        if (aimTest.m_IsPassed)
        {
            auto maxHeightTest = MaxHeightTest(aimTest, groundTest);

            TrySetState(maxHeightTest.m_IsPassed
                            ? BuildState::STATE_CAN_BUILD
                            : BuildState::STATE_CANNOT_BUILD);

            GetTransform()->GetPosition()->setVector(maxHeightTest.m_Origin);
            GetTransform()->GetRotation()->y(180 + maxHeightTest.m_Angle);

            return;
        }
        else
        {
            TrySetState(BuildState::STATE_CAN_BUILD);

            GetTransform()->GetPosition()->setVector(groundTest.m_Origin);
            GetTransform()->GetRotation()->y(180 + groundTest.m_Angle);

            return;
        }
    }

    TrySetState(BuildState::STATE_CANNOT_BUILD);

    GetTransform()->GetPosition()->setVector(viewPoint);
    GetTransform()->GetRotation()->y(180 + angles.y);
}

AimTestResult FoundationBase::MaxHeightTest(AimTestResult aimTest, AimTestResult groundTest)
{
    auto isTooHigh = groundTest.m_Origin.z < aimTest.m_Origin.z;

    return AimTestResult(!isTooHigh, aimTest.m_Origin, aimTest.m_Angle);
}

AimTestResult FoundationBase::MinHeightTest(AimTestResult aimTest, AimTestResult groundTest)
{
    auto isTooLow = aimTest.m_Origin.z < groundTest.m_Origin.z;

    return AimTestResult(!isTooLow, aimTest.m_Origin);
}

AimTestResult FoundationBase::IntersectionTest(AimTestResult result)
{
    auto objects = ObjectManager::Instance().GetObjectsInArea(result.m_Origin);

    auto shape = GetShape(AimTestResult(
        result.m_IsPassed,
        result.m_Origin,
        result.m_Angle + 180));

    for (auto object : objects)
    {
        if (object.empty() || object.expired())
            continue;

        auto foundation = dynamic_cast<FoundationBase *>(*object.lock());

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

Shape FoundationBase::GetShape()
{
    return GetShape(AimTestResult(
        true,
        *GetTransform()->GetPosition(),
        GetTransform()->GetRotation()->y()));
}