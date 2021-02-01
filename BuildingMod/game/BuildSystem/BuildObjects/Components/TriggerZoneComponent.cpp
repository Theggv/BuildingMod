#include "TriggerZoneComponent.h"

TriggerZoneComponent::TriggerZoneComponent()
{
}

TriggerZoneComponent::~TriggerZoneComponent()
{
    delete m_Handler;
}

AimTestResult TriggerZoneComponent::TryConnect(ray ray, GameObject *object)
{
    vec3 hit;
    bool intersection;

    int minRayLength = 75;
    bool minLengthTest;

    int minZone = -1;
    double minLengthSquared = 0;
    double curLengthSquared;

    for (size_t zoneId = 0; zoneId < m_Zones.size(); zoneId++)
    {
        auto transformedZone = GetTransformedZone(m_parent, zoneId);

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

    return m_Handler->GetConnectionPoint(m_parent, object, minZone);
}
