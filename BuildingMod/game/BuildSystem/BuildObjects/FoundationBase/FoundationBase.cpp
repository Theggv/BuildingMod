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

    auto aimTestResult = FoundationAimTest(aimRay);

    auto traceGroundTestResult = TraceGroundTest(
        aimTestResult.m_IsPassed
            ? aimTestResult.m_Origin
            : viewPoint,
        angles);

    if (aimTestResult.m_IsPassed && traceGroundTestResult.m_IsPassed)
    {
        if (traceGroundTestResult.m_Origin.z < aimTestResult.m_Origin.z)
        {
            TrySetState(BuildState::STATE_CANNOT_BUILD);

            GetTransform()->GetPosition()->setVector(
                aimTestResult.m_Origin.x,
                aimTestResult.m_Origin.y,
                aimTestResult.m_Origin.z);

            GetTransform()->GetRotation()->y(180 + aimTestResult.m_Angle);

            return;
        }
    }

    TrySetState(traceGroundTestResult.m_IsPassed
                    ? BuildState::STATE_CAN_BUILD
                    : BuildState::STATE_CANNOT_BUILD);

    if (traceGroundTestResult.m_IsPassed)
    {
        GetTransform()->GetPosition()->setVector(
            traceGroundTestResult.m_Origin.x,
            traceGroundTestResult.m_Origin.y,
            traceGroundTestResult.m_Origin.z);

        GetTransform()->GetRotation()->y(
            180 + (aimTestResult.m_IsPassed
                       ? aimTestResult.m_Angle
                       : angles.y));
    }
    else
    {
        GetTransform()->GetPosition()->setVector(viewPoint.x, viewPoint.y, viewPoint.z);
        GetTransform()->GetRotation()->y(180 + angles.y);
    }
}

void ConnectFoundations(FoundationBase *, FoundationBase *)
{
}

std::vector<Triangle> FoundationBase::GenerateTriangles(
    vec2 a, vec2 b, vec2 c, vec2 d, vec2 heights)
{
    std::vector<Triangle> triangles;
    std::vector<Triangle> buffer;

    auto minHeight = heights.x;
    auto maxHeight = heights.y;

    // a; b
    buffer = Shape({vec3(a.x, a.y, minHeight),
                    vec3(a.x, a.y, maxHeight),
                    vec3(b.x, b.y, maxHeight),
                    vec3(b.x, b.y, minHeight)})
                 .Triangulate();
    triangles.insert(triangles.end(), buffer.begin(), buffer.end());

    // b; c
    buffer = Shape({vec3(b.x, b.y, minHeight),
                    vec3(b.x, b.y, maxHeight),
                    vec3(c.x, c.y, maxHeight),
                    vec3(c.x, c.y, minHeight)})
                 .Triangulate();
    triangles.insert(triangles.end(), buffer.begin(), buffer.end());

    // c; d
    buffer = Shape({vec3(c.x, c.y, minHeight),
                    vec3(c.x, c.y, maxHeight),
                    vec3(d.x, d.y, maxHeight),
                    vec3(d.x, d.y, minHeight)})
                 .Triangulate();
    triangles.insert(triangles.end(), buffer.begin(), buffer.end());

    // d; a
    buffer = Shape({vec3(d.x, d.y, minHeight),
                    vec3(d.x, d.y, maxHeight),
                    vec3(a.x, a.y, maxHeight),
                    vec3(a.x, a.y, minHeight)})
                 .Triangulate();
    triangles.insert(triangles.end(), buffer.begin(), buffer.end());

    return triangles;
}