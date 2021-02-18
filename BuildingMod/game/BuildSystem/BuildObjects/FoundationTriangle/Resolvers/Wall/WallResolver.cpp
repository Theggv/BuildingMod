#include "WallResolver.h"

// objects
#include "../../FoundationTriangle.h"
#include <game/BuildSystem/BuildObjects/WallBase/WallBase.h>

// point generators
#include "WallPoints.h"

using namespace FoundationTriangleResolvers;

WallResolver::WallResolver()
{
    auto wallPoint = new WallPoints;

    m_Handler = wallPoint;

    GenerateZones();
}

bool WallResolver::CanResolve(GameObject *object, GameObject *bindable)
{
    if (dynamic_cast<FoundationTriangle *>(object) != nullptr &&
        dynamic_cast<WallBase *>(bindable) != nullptr)
        return true;

    return false;
}

void WallResolver::GenerateZones()
{
    m_Zones.clear();

    for (size_t zone = 0; zone < 3; zone++)
    {
        m_Zones.push_back(GenerateZone(zone));
    }
}

bool WallResolver::HasConnection(TriangleZones zone)
{
    if (m_Connections.find(static_cast<int>(zone)) == m_Connections.end())
        return false;

    return true;
}

vector<Triangle> WallResolver::GenerateZone(int zoneId)
{
    std::vector<Triangle> triangles;

    // Return empty list if zone is not empty
    if (HasConnection(static_cast<TriangleZones>(zoneId)))
        return triangles;

    auto minHeight = -30;
    auto maxHeight = 30;

    // smari shemu, down

    auto a = vec2(0, 2 * FoundationTriangle::m_Height / 3);
    auto b = a.Transform(mat4::RotationMatrix(-120));
    auto c = a.Transform(mat4::RotationMatrix(120));

    switch (static_cast<TriangleZones>(zoneId))
    {
    case TriangleZones::RIGHT:

        triangles = Shape({vec3(a.x, a.y, minHeight),
                           vec3(a.x, a.y, maxHeight),
                           vec3(b.x, b.y, maxHeight),
                           vec3(b.x, b.y, minHeight)})
                        .Triangulate();
        break;
    case TriangleZones::DOWN:

        triangles = Shape({vec3(b.x, b.y, minHeight),
                           vec3(b.x, b.y, maxHeight),
                           vec3(c.x, c.y, maxHeight),
                           vec3(c.x, c.y, minHeight)})
                        .Triangulate();
        break;

    case TriangleZones::LEFT:

        triangles = Shape({vec3(c.x, c.y, minHeight),
                           vec3(c.x, c.y, maxHeight),
                           vec3(a.x, a.y, maxHeight),
                           vec3(a.x, a.y, minHeight)})
                        .Triangulate();
        break;
    }

    return triangles;
}

vector<Triangle> WallResolver::GetTransformedZone(GameObject *object, int zoneId)
{
    vector<Triangle> tries;

    // Transform
    vec3 pos = *object->GetTransform()->GetPosition();
    vec3 rot = *object->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(-90 - rot.y) *
               mat4::TranslateMatrix(pos);

    for (auto &triangle : m_Zones[zoneId])
    {
        tries.push_back(triangle.Transform(mat));
    }

    return tries;
}