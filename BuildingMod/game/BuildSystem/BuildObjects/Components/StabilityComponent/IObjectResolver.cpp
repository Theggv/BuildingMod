#include "IObjectResolver.h"
#include "IConnectionPoints.h"
#include "../IStabilityComponent.h"

IObjectResolver::~IObjectResolver()
{
    delete m_Successor;
    delete m_Handler;
}

void IObjectResolver::SetSuccessor(IObjectResolver *successor)
{
    m_Successor = successor;
}

void IObjectResolver::AddConnection(GameObject *object, GameObject *bindable)
{
    if (!CanResolve(object, bindable))
    {
        if (m_Successor != nullptr)
            m_Successor->AddConnection(object, bindable);

        return;
    }

    auto zoneId = m_Handler->GetZoneIdByPosition(
        object,
        bindable,
        *bindable->GetTransform()->GetPosition());

    if (zoneId < 0)
        return;

    if (m_Connections.find(zoneId) != m_Connections.end())
    {
        m_Connections[zoneId] = object;
    }
    else
    {
        m_Connections.insert(pair<int, GameObject *>(
            zoneId, object));
    }

    GenerateZones();
}

bool IObjectResolver::HasConnection(GameObject *object, GameObject *bindable, vec3 pos)
{
    if (!CanResolve(object, bindable))
    {
        if (m_Successor != nullptr)
            return m_Successor->HasConnection(object, bindable, pos);
    }

    auto zoneId = m_Handler->GetZoneIdByPosition(
        object,
        bindable, pos);

    if (zoneId < 0)
        return false;

    if (m_Connections.find(zoneId) != m_Connections.end())
    {
        return true;
    }

    return false;
}

AimTestResult IObjectResolver::TryConnect(ray ray, GameObject *object, GameObject *bindable)
{
    if (!CanResolve(object, bindable))
        return CallNext(ray, object, bindable);

    vec3 hit;
    bool intersection;

    int minRayLength = 75;
    bool minLengthTest;

    int minZone = -1;
    double minLengthSquared = 0;
    double curLengthSquared;

    for (size_t zoneId = 0; zoneId < m_Zones.size(); zoneId++)
    {
        auto transformedZone = GetTransformedZone(object, zoneId);

        for (auto triangle : transformedZone)
        {
            intersection = triangle.RayIntersection(ray, hit);

            if (!intersection)
                continue;

            curLengthSquared = (hit - ray.GetOrigin()).LengthSquared();
            minLengthTest = curLengthSquared >= minRayLength * minRayLength;

            if (!minLengthTest)
                continue;

            if (!minLengthSquared || curLengthSquared < minLengthSquared)
            {
                minLengthSquared = curLengthSquared;
                minZone = zoneId;
            }
        }
    }

    if (minZone == -1)
        return AimTestResult(false);

    return m_Handler->GetConnectionPoint(object, bindable, minZone);
}

vector<Triangle> IObjectResolver::GetTransformedZone(GameObject *object, int zoneId)
{
    vector<Triangle> tries;

    // Transform
    vec3 pos = *object->GetTransform()->GetPosition();
    vec3 rot = *object->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(90 - rot.y) *
               mat4::TranslateMatrix(pos);

    for (auto &triangle : m_Zones[zoneId])
    {
        tries.push_back(triangle.Transform(mat));
    }

    return tries;
}

AimTestResult IObjectResolver::CallNext(ray ray, GameObject *object, GameObject *bindable)
{
    if (m_Successor != nullptr)
        return m_Successor->TryConnect(ray, object, bindable);

    return AimTestResult(false);
}
