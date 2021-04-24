#include "WallResolver.h"

// point generators
#include "WallPoints.h"

using namespace FoundationTriangleResolvers;

WallResolver::WallResolver()
{
    auto wallPoint = new WallPoints;

    m_Handler = wallPoint;

    GenerateZones();
}

bool WallResolver::CanResolve(p_GameObject_t object, p_GameObject_t bindable)
{
    if (dynamic_pointer_cast<FoundationTriangle>(object) != nullptr &&
        dynamic_pointer_cast<WallBase>(bindable) != nullptr)
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

vector<Triangle> WallResolver::GenerateZone(int zoneId)
{
    std::vector<Triangle> triangles;

    // Return empty list if zone is not empty
    if (HasConnection(zoneId))
        return triangles;

    auto minHeight = -30;
    auto maxHeight = 30;

    auto a = vec2(0, 2 * FoundationTriangle::m_Height / 3);
    auto b = a.Transform(mat4::RotationMatrix(-120));
    auto c = a.Transform(mat4::RotationMatrix(120));

    switch (static_cast<TriangleZones>(zoneId))
    {
    case TriangleZones::RIGHT:
        return Shape({vec3(a.x, a.y, minHeight),
                      vec3(a.x, a.y, maxHeight),
                      vec3(b.x, b.y, maxHeight),
                      vec3(b.x, b.y, minHeight)})
            .Triangulate();

    case TriangleZones::DOWN:
        return Shape({vec3(b.x, b.y, minHeight),
                      vec3(b.x, b.y, maxHeight),
                      vec3(c.x, c.y, maxHeight),
                      vec3(c.x, c.y, minHeight)})
            .Triangulate();

    case TriangleZones::LEFT:
        return Shape({vec3(c.x, c.y, minHeight),
                      vec3(c.x, c.y, maxHeight),
                      vec3(a.x, a.y, maxHeight),
                      vec3(a.x, a.y, minHeight)})
            .Triangulate();
    }

    return triangles;
}

vector<Triangle> WallResolver::GetTransformedZone(p_GameObject_t object, int zoneId)
{
    vector<Triangle> tries;

    // Transform
    vec3 pos = *object->GetTransform()->GetPosition();
    vec3 rot = *object->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(rot.y - 90) *
               mat4::TranslateMatrix(pos);

    for (auto &triangle : m_Zones[zoneId])
    {
        tries.push_back(triangle.Transform(mat));
    }

    return tries;
}