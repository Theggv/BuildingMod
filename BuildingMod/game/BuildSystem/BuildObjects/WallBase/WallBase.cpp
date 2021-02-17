#include "WallBase.h"

#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IColliderComponent.h>
#include <game/BuildSystem/BuildObjects/Components/VisualizerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/IStabilityComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>

// other objects
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>

const double WallBase::m_ModelSize = 112;

WallBase::WallBase(edict_t *owner)
{
    AddComponent(new OwnerComponent(owner));

    auto visualizer = new VisualizerComponent(0.3);
    visualizer->Disable();

    AddComponent(visualizer);
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

        auto gameObject = *object.lock();

        if (gameObject->Id == this->Id)
            continue;

        if (dynamic_cast<FoundationBase *>(gameObject) != nullptr ||
            dynamic_cast<WallBase *>(gameObject) != nullptr)
        {
            Connect(gameObject);
        }
    }
}

void WallBase::Connect(GameObject *other)
{
    this->GetComponent<IStabilityComponent>()->AddConnection(other);
    other->GetComponent<IStabilityComponent>()->AddConnection(this);
}

void WallBase::AimPointHandler()
{
    auto ownerComponent = GetComponent<OwnerComponent>();

    auto viewPoint = ownerComponent->GetAimDest(250.0);

    auto aimRay = ownerComponent->GetAimRay(viewPoint, 500.0);
    auto angles = ownerComponent->GetViewAngles();

    auto aimTest = AimTest(aimRay);
    auto interTest = IntersectionTest(aimTest);

    if (aimTest.m_IsPassed && interTest.m_IsPassed)
    {
        TrySetState(BuildState::STATE_CAN_BUILD);

        GetTransform()->GetPosition()->setVector(interTest.m_Origin);
        GetTransform()->GetRotation()->y(interTest.m_Angle);
    }
    else
    {
        TrySetState(BuildState::STATE_CANNOT_BUILD);

        GetTransform()->GetPosition()->setVector(viewPoint);
        GetTransform()->GetRotation()->y(angles.y);
    }
}

AimTestResult WallBase::IntersectionTest(AimTestResult result)
{
    // zaglushka
    return result;

    // Skip test if previous was failed
    if (!result.m_IsPassed)
        return result;

    auto objects = ObjectManager::Instance().GetObjectsInArea(result.m_Origin);

    auto shape = GetShape(AimTestResult(
        result.m_IsPassed,
        result.m_Origin,
        result.m_Angle + 180));

    for (auto object : objects)
    {
        if (object.empty() || object.expired())
            continue;

        auto gameObject = *object.lock();

        if (gameObject->Id == this->Id)
            continue;

        auto wall = dynamic_cast<WallBase *>(gameObject);

        if (wall != nullptr)
        {
            auto otherShape = wall->GetShape();

            if (shape.IsIntersect(otherShape))
                return AimTestResult(false, result.m_Origin, result.m_Angle);
        }
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