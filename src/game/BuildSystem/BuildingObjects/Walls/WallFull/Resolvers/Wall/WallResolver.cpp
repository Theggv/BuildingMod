#include "WallResolver.h"

// point generators
#include "WallPoints.h"

using namespace WallFullResolvers;

WallResolver::WallResolver()
{
    auto wallPoint = new WallPoints;

    m_Handler = wallPoint;

    GenerateZones();
}

bool WallResolver::CanResolve(p_GameObject_t object, p_GameObject_t bindable)
{
    if (dynamic_pointer_cast<WallBase>(object) == nullptr ||
        dynamic_pointer_cast<WallBase>(bindable) == nullptr)
        return false;

    return true;
}

void WallResolver::GenerateZones()
{
    m_Zones.clear();
    m_Zones.push_back(GenerateZone());
}

bool WallResolver::HasConnection()
{
    if (m_Connections.find(0) != m_Connections.end())
        return m_Connections[0].lock() != nullptr;

    return false;
}

vector<Triangle> WallResolver::GenerateZone()
{
    vector<Triangle> triangles;

    // Return empty list if zone is not empty
    if (HasConnection())
        return triangles;

    auto width = WallBase::m_ModelSize;

    auto minHeight = 0;
    auto maxHeight = width + width / 2;

    return Shape({vec3(0, -width / 2, minHeight),
                  vec3(0, width / 2, minHeight),
                  vec3(0, width / 2, maxHeight),
                  vec3(0, -width / 2, maxHeight)})
        .Triangulate();
}

bool WallResolver::IsTouch(Shape s1, Shape s2)
{
    auto p1 = s1.GetPoints();
    auto p2 = s2.GetPoints();

    if (vec2(p1[0]) == vec2(p2[0]) && vec2(p1[1]) == vec2(p2[1]) ||
        vec2(p1[0]) == vec2(p2[1]) && vec2(p1[1]) == vec2(p2[0]))
    {
        // s2 should be higher than s1
        if (p2[0].z > p1[0].z &&
            p2[0].z == p1[2].z)
        {
            return true;
        }
    }

    return false;
}
