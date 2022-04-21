#include "FoundationResolver.h"

// point generators
#include "TriangleToSquarePoints.h"
#include "TriangleToTrianglePoints.h"

using namespace FoundationTriangleResolvers;

FoundationResolver::FoundationResolver()
{
    auto triangleToSquare = new TriangleToSquarePoints;
    auto triangleToTriangle = new TriangleToTrianglePoints;

    triangleToSquare->SetSuccessor(triangleToTriangle);

    m_Handler = triangleToSquare;

    GenerateZones();
}

void FoundationResolver::GenerateZones()
{
    m_Zones.clear();

    for (size_t height = 0; height < 3; height++)
    {
        for (size_t zone = 0; zone < 3; zone++)
        {
            m_Zones.push_back(GenerateZone(
                GetZoneId(zone, height)));
        }
    }
}

bool FoundationResolver::CanResolve(GameObject *object, GameObject *bindable)
{
    if (dynamic_cast<FoundationTriangle *>(object) != nullptr &&
        dynamic_cast<FoundationBase *>(bindable) != nullptr)
        return true;

    return false;
}

TriangleZones FoundationResolver::GetZoneById(int zoneId)
{
    return static_cast<TriangleZones>(zoneId % 3);
}

HeightZones FoundationResolver::GetHeightById(int zoneId)
{
    return static_cast<HeightZones>(zoneId / 3);
}

int FoundationResolver::GetZoneId(int zone, int height)
{
    return zone + height * 3;
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

    auto hasRight = HasConnection(static_cast<int>(TriangleZones::RIGHT));
    auto hasDown = HasConnection(static_cast<int>(TriangleZones::DOWN));
    auto hasLeft = HasConnection(static_cast<int>(TriangleZones::LEFT));

    // smari shemu, down

    auto a = vec2(0, 2 * FoundationTriangle::m_Height / 3);
    auto b = a.Transform(mat4::RotationMatrix(-120));
    auto c = a.Transform(mat4::RotationMatrix(120));

    auto d = vec2(0, 5 * FoundationTriangle::m_Height / 3);
    auto e = d.Transform(mat4::RotationMatrix(-120));
    auto f = d.Transform(mat4::RotationMatrix(120));

    auto tempVector = vec2(0, ((d - a) / 2).Length() / (sin(60 * M_PI / 180)));

    auto aRight = a + tempVector.Transform(mat4::RotationMatrix(-30));
    auto aLeft = a + tempVector.Transform(mat4::RotationMatrix(30));

    auto bRight = b + tempVector.Transform(mat4::RotationMatrix(-90));
    auto bDown = b + tempVector.Transform(mat4::RotationMatrix(-150));

    auto cLeft = c + tempVector.Transform(mat4::RotationMatrix(90));
    auto cDown = c + tempVector.Transform(mat4::RotationMatrix(150));

    switch (zone)
    {
    case TriangleZones::RIGHT:

        return Triangle::GenerateTriangles(
            a,
            hasLeft ? aRight : d,
            hasDown ? bRight : e,
            b,
            heights[static_cast<int>(heightZone)]);

    case TriangleZones::DOWN:

        return Triangle::GenerateTriangles(
            b,
            hasRight ? bDown : e,
            hasLeft ? cDown : f,
            c,
            heights[static_cast<int>(heightZone)]);

    case TriangleZones::LEFT:

        return Triangle::GenerateTriangles(
            c,
            hasDown ? cLeft : f,
            hasRight ? aLeft : d,
            a,
            heights[static_cast<int>(heightZone)]);
    }

    return triangles;
}

vector<Triangle> FoundationResolver::GetTransformedZone(GameObject *object, int zoneId)
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