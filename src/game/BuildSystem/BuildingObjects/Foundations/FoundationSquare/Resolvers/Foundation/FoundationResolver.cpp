#include "FoundationResolver.h"

// objects
#include "../../FoundationSquare.h"

// point generators
#include "SquareToSquarePoints.h"
#include "SquareToTrianglePoints.h"

using namespace FoundationSquareResolvers;

FoundationResolver::FoundationResolver()
{
    auto squareToSquare = new SquareToSquarePoints;
    auto squareToTriangle = new SquareToTrianglePoints;

    squareToSquare->SetSuccessor(squareToTriangle);

    m_Handler = squareToSquare;

    GenerateZones();
}

bool FoundationResolver::CanResolve(p_GameObject_t object, p_GameObject_t bindable)
{
    if (dynamic_pointer_cast<FoundationSquare>(object) != nullptr &&
        dynamic_pointer_cast<FoundationBase>(bindable) != nullptr)
        return true;

    return false;
}

void FoundationResolver::GenerateZones()
{
    m_Zones.clear();

    for (size_t heightZone = 0; heightZone < 3; heightZone++)
    {
        for (size_t zone = 0; zone < 4; zone++)
        {
            m_Zones.push_back(GenerateZone(
                GetZoneId(zone, heightZone)));
        }
    }
}

SquareZones FoundationResolver::GetZoneById(int zoneId)
{
    return static_cast<SquareZones>(zoneId % 4);
}

HeightZones FoundationResolver::GetHeightById(int zoneId)
{
    return static_cast<HeightZones>(zoneId / 4);
}

int FoundationResolver::GetZoneId(int zone, int height)
{
    return zone + height * 4;
}

vector<Triangle> FoundationResolver::GenerateZone(int zoneId)
{
    std::vector<Triangle> triangles;

    auto zone = GetZoneById(zoneId);
    auto heightZone = GetHeightById(zoneId);

    // Return empty list if zone is not empty
    if (HasConnection(static_cast<int>(zone)))
        return triangles;

    // list of heights (min, max)
    std::vector<vec2> heights = {vec2(-128, -30), vec2(-30, 30), vec2(30, 128)};

    auto minHeight = heights[static_cast<int>(heightZone)].x;
    auto maxHeight = heights[static_cast<int>(heightZone)].y;

    auto hasRight = HasConnection(static_cast<int>(SquareZones::RIGHT));
    auto hasDown = HasConnection(static_cast<int>(SquareZones::DOWN));
    auto hasLeft = HasConnection(static_cast<int>(SquareZones::LEFT));
    auto hasUp = HasConnection(static_cast<int>(SquareZones::UP));

    auto width = FoundationSquare::m_ModelSize;

    switch (zone)
    {
    case SquareZones::RIGHT:

        return Triangle::GenerateTriangles(
            vec2(width / 2, width / 2),
            hasUp ? vec2(width, width / 2) : vec2(width, width),
            hasDown ? vec2(width, -width / 2) : vec2(width, -width),
            vec2(width / 2, -width / 2),
            heights[static_cast<int>(heightZone)]);
    case SquareZones::DOWN:

        return Triangle::GenerateTriangles(
            vec2(width / 2, -width / 2),
            hasRight ? vec2(width / 2, -width) : vec2(width, -width),
            hasLeft ? vec2(-width / 2, -width) : vec2(-width, -width),
            vec2(-width / 2, -width / 2),
            heights[static_cast<int>(heightZone)]);

    case SquareZones::LEFT:

        return Triangle::GenerateTriangles(
            vec2(-width / 2, -width / 2),
            hasDown ? vec2(-width, -width / 2) : vec2(-width, -width),
            hasUp ? vec2(-width, width / 2) : vec2(-width, width),
            vec2(-width / 2, width / 2),
            heights[static_cast<int>(heightZone)]);

    case SquareZones::UP:

        return Triangle::GenerateTriangles(
            vec2(-width / 2, width / 2),
            hasLeft ? vec2(-width / 2, width) : vec2(-width, width),
            hasRight ? vec2(width / 2, width) : vec2(width, width),
            vec2(width / 2, width / 2),
            heights[static_cast<int>(heightZone)]);
    }

    return triangles;
}

vector<Triangle> FoundationResolver::GetTransformedZone(p_GameObject_t object, int zoneId)
{
    vector<Triangle> tries;

    // Transform
    vec3 pos = *object->GetTransform()->GetPosition();
    vec3 rot = *object->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(rot.y) *
               mat4::TranslateMatrix(pos);

    for (auto &triangle : m_Zones[zoneId])
    {
        tries.push_back(triangle.Transform(mat));
    }

    return tries;
}