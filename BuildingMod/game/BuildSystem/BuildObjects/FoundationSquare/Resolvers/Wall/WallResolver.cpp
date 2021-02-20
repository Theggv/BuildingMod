#include "WallResolver.h"

// objects
#include "../../FoundationSquare.h"
#include <game/BuildSystem/BuildObjects/WallBase/WallBase.h>

// point generators
#include "WallPoints.h"

using namespace FoundationSquareResolvers;

WallResolver::WallResolver()
{
    auto wallPoint = new WallPoints;

    m_Handler = wallPoint;

    GenerateZones();
}

bool WallResolver::CanResolve(GameObject *object, GameObject *bindable)
{
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

vector<Triangle> WallResolver::GenerateZone(int zoneId)
{
    std::vector<Triangle> triangles;

    // Return empty list if zone is not empty
    if (HasConnection(zoneId))
        return triangles;

    auto minHeight = -30;
    auto maxHeight = 30;

    auto width = FoundationSquare::m_ModelSize;

    switch (static_cast<SquareZones>(zoneId))
    {
    case SquareZones::RIGHT:

        return Shape({vec3(width / 2, width / 2, minHeight),
                      vec3(width / 2, width / 2, maxHeight),
                      vec3(width / 2, -width / 2, maxHeight),
                      vec3(width / 2, -width / 2, minHeight)})
            .Triangulate();

    case SquareZones::DOWN:

        return Shape({vec3(-width / 2, -width / 2, minHeight),
                      vec3(-width / 2, -width / 2, maxHeight),
                      vec3(width / 2, -width / 2, maxHeight),
                      vec3(width / 2, -width / 2, minHeight)})
            .Triangulate();

    case SquareZones::LEFT:

        return Shape({vec3(-width / 2, width / 2, minHeight),
                      vec3(-width / 2, width / 2, maxHeight),
                      vec3(-width / 2, -width / 2, maxHeight),
                      vec3(-width / 2, -width / 2, minHeight)})
            .Triangulate();

    case SquareZones::UP:

        return Shape({vec3(-width / 2, width / 2, minHeight),
                      vec3(-width / 2, width / 2, maxHeight),
                      vec3(width / 2, width / 2, maxHeight),
                      vec3(width / 2, width / 2, minHeight)})
            .Triangulate();
    }

    return triangles;
}