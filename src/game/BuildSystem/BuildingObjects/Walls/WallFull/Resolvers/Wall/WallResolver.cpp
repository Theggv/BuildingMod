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

bool WallResolver::CanResolve(GameObject *object, GameObject *bindable)
{
    // NOTE - temporary
    return false;

    if (dynamic_cast<FoundationSquare *>(object) != nullptr &&
        dynamic_cast<WallBase *>(bindable) != nullptr)
        return true;

    return false;
}

void WallResolver::GenerateZones()
{
    m_Zones.clear();

    for (size_t zone = 0; zone < 4; zone++)
    {
        m_Zones.push_back(GenerateZone(zone));
    }
}

bool WallResolver::HasConnection(SquareZones zone)
{
    if (m_Connections.find(static_cast<int>(zone)) == m_Connections.end())
        return false;

    return true;
}

vector<Triangle> WallResolver::GenerateZone(int zoneId)
{
    std::vector<Triangle> triangles;
    std::vector<Triangle> buffer;

    // Return empty list if zone is not empty
    if (HasConnection(static_cast<SquareZones>(zoneId)))
        return triangles;

    auto minHeight = -30;
    auto maxHeight = 30;

    auto hasRight = HasConnection(SquareZones::RIGHT);
    auto hasDown = HasConnection(SquareZones::DOWN);
    auto hasLeft = HasConnection(SquareZones::LEFT);
    auto hasUp = HasConnection(SquareZones::UP);

    auto width = FoundationSquare::m_ModelSize;

    switch (static_cast<SquareZones>(zoneId))
    {
    case SquareZones::RIGHT:

        triangles = Shape({vec3(width / 2, width / 2, minHeight),
                           vec3(width / 2, width / 2, maxHeight),
                           vec3(width / 2, -width / 2, maxHeight),
                           vec3(width / 2, -width / 2, minHeight)})
                        .Triangulate();

        break;
    case SquareZones::DOWN:

        triangles = Shape({vec3(-width / 2, -width / 2, minHeight),
                           vec3(-width / 2, -width / 2, maxHeight),
                           vec3(width / 2, -width / 2, maxHeight),
                           vec3(width / 2, -width / 2, minHeight)})
                        .Triangulate();

        break;
    case SquareZones::LEFT:

        triangles = Shape({vec3(-width / 2, width / 2, minHeight),
                           vec3(-width / 2, width / 2, maxHeight),
                           vec3(-width / 2, -width / 2, maxHeight),
                           vec3(-width / 2, -width / 2, minHeight)})
                        .Triangulate();

        break;
    case SquareZones::UP:

        triangles = Shape({vec3(-width / 2, width / 2, minHeight),
                           vec3(-width / 2, width / 2, maxHeight),
                           vec3(width / 2, width / 2, maxHeight),
                           vec3(width / 2, width / 2, minHeight)})
                        .Triangulate();

        break;
    }

    return triangles;
}