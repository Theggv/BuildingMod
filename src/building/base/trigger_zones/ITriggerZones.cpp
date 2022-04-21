#include "ITriggerZones.h"
#include <building/base/GameObject.h>

double ITriggerZones::GetDistanceToZone(GameObject *object, Ray ray, int packedIndex, int minRayLength)
{
    vec3 hit;
    bool intersection;

    bool minLengthTest;

    double minLengthSquared = 0;
    double curLengthSquared;

    auto transformedZone = GetTransformedZone(object, packedIndex);

    for (auto &triangle : transformedZone)
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
        }
    }

    return minLengthSquared;
}

std::vector<Triangle>
ITriggerZones::GetTransformedZone(GameObject *object, int packedIndex)
{
    std::vector<Triangle> triangles;

    // Transform
    vec3 pos = *object->GetTransform()->GetPosition();
    vec3 rot = *object->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(rot.y) *
               mat4::TranslateMatrix(pos);

    for (auto &triangle : m_TriggerZones[packedIndex])
    {
        triangles.push_back(triangle.Transform(mat));
    }

    return triangles;
}
