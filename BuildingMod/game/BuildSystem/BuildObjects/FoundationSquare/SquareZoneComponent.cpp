#include "SquareZoneComponent.h"

// objects
#include "FoundationSquare.h"

// point generators
#include "SquareToSquarePoints.h"
#include "SquareToTrianglePoints.h"

SquareZoneComponent::SquareZoneComponent()
{
    auto squareToSquare = new SquareToSquarePoints;
    auto squareToTriangle = new SquareToTrianglePoints;

    squareToSquare->SetSuccessor(squareToTriangle);

    m_Handler = squareToSquare;

    GenerateZones();
}

void SquareZoneComponent::GenerateZones()
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

void SquareZoneComponent::AddConnection(GameObject *object)
{
    auto objectPos = vec2(*object->GetTransform()->GetPosition()).Round();

    for (size_t zone = 0; zone < 4; zone++)
    {
        auto point = vec2(m_Handler->GetConnectionPoint(m_parent, object, zone).m_Origin).Round();

        if (objectPos == point)
        {
            m_Connections[zone] = ObjectManager::Instance().GetPtr(object->Id);

            // Regenerate zones after change
            GenerateZones();
        }
    }
}

bool SquareZoneComponent::HasConnection(SquareZones zone)
{
    if (m_Connections[static_cast<int>(zone)].empty() ||
        m_Connections[static_cast<int>(zone)].expired())
        return false;

    return true;
}

SquareZones SquareZoneComponent::GetZoneById(int zoneId)
{
    return static_cast<SquareZones>(zoneId % 4);
}

HeightZones SquareZoneComponent::GetHeightById(int zoneId)
{
    return static_cast<HeightZones>(zoneId / 4);
}

int SquareZoneComponent::GetZoneId(int zone, int height)
{
    return zone + height * 4;
}

vector<Triangle> SquareZoneComponent::GenerateZone(int zoneId)
{
    std::vector<Triangle> triangles;
    std::vector<Triangle> buffer;

    auto zone = GetZoneById(zoneId);
    auto heightZone = GetHeightById(zoneId);

    // Return empty list if zone is not empty
    if (HasConnection(zone))
        return triangles;

    // list of heights (min, max)
    std::vector<vec2> heights = {vec2(-128, -30), vec2(-30, 30), vec2(30, 128)};

    auto minHeight = heights[static_cast<int>(heightZone)].x;
    auto maxHeight = heights[static_cast<int>(heightZone)].y;

    auto hasRight = HasConnection(SquareZones::RIGHT);
    auto hasDown = HasConnection(SquareZones::DOWN);
    auto hasLeft = HasConnection(SquareZones::LEFT);
    auto hasUp = HasConnection(SquareZones::UP);

    auto width = FoundationSquare::m_ModelSize;

    switch (zone)
    {
    case SquareZones::RIGHT:

        // cw
        triangles = Triangle::GenerateTriangles(
            vec2(width / 2, width / 2),
            hasUp ? vec2(width, width / 2) : vec2(width, width),
            hasDown ? vec2(width, -width / 2) : vec2(width, -width),
            vec2(width / 2, -width / 2),
            heights[static_cast<int>(heightZone)]);

        break;
    case SquareZones::DOWN:

        // cw
        triangles = Triangle::GenerateTriangles(
            vec2(width / 2, -width / 2),
            hasRight ? vec2(width / 2, -width) : vec2(width, -width),
            hasLeft ? vec2(-width / 2, -width) : vec2(-width, -width),
            vec2(-width / 2, -width / 2),
            heights[static_cast<int>(heightZone)]);

        break;
    case SquareZones::LEFT:

        // cw
        triangles = Triangle::GenerateTriangles(
            vec2(-width / 2, -width / 2),
            hasDown ? vec2(-width, -width / 2) : vec2(-width, -width),
            hasUp ? vec2(-width, width / 2) : vec2(-width, width),
            vec2(-width / 2, width / 2),
            heights[static_cast<int>(heightZone)]);

        break;
    case SquareZones::UP:

        // cw
        triangles = Triangle::GenerateTriangles(
            vec2(-width / 2, width / 2),
            hasLeft ? vec2(-width / 2, width) : vec2(-width, width),
            hasRight ? vec2(width / 2, width) : vec2(width, width),
            vec2(width / 2, width / 2),
            heights[static_cast<int>(heightZone)]);

        break;
    }

    return triangles;
}

vector<Triangle> SquareZoneComponent::GetTransformedZone(GameObject *object, int zoneId)
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