#include "TriangleToSquarePoints.h"
#include <game/BuildSystem/BuildingObjects/Foundations/Foundations.h>

AimTestResult TriangleToSquarePoints::GetConnectionPoint(
    GameObject *object, GameObject *bindable, int zoneId)
{
    if (dynamic_cast<FoundationSquare *>(bindable) == nullptr)
        return CallNext(object, bindable, zoneId);

    auto foundation = dynamic_cast<FoundationTriangle *>(object);

    if (foundation == nullptr)
        return CallNext(object, bindable, zoneId);

    TriangleZones zone;
    HeightZones heightZone;
    ConvertZoneId(zoneId, zone, heightZone);

    double heights[3] = {-foundation->m_ModelSize / 2.0, 0, foundation->m_ModelSize / 2.0};
    auto height = heights[static_cast<int>(heightZone)];

    vec3 newPos = vec3(0, foundation->m_ModelSize / 2 + FoundationTriangle::m_Height / 3, height);

    vec3 pos = *foundation->GetTransform()->GetPosition();
    vec3 rot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(rot.y - 90) *
               mat4::TranslateMatrix(pos);

    switch (zone)
    {
    case TriangleZones::RIGHT:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(-60) * mat),
                             rot.y - 60);
    case TriangleZones::DOWN:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(180) * mat),
                             rot.y + 180);
    case TriangleZones::LEFT:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(60) * mat),
                             rot.y + 60);

    default:
        return AimTestResult(false);
    }
}

int TriangleToSquarePoints::GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos)
{
    if (dynamic_cast<FoundationSquare *>(bindable) == nullptr)
        return CallNext(object, bindable, pos);

    auto foundation = dynamic_cast<FoundationTriangle *>(object);

    vec3 newPos = vec3(0, foundation->m_ModelSize / 2 + FoundationTriangle::m_Height / 3, 0);

    vec3 objectPos = *foundation->GetTransform()->GetPosition();
    vec3 objectRot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(objectRot.y - 90) *
               mat4::TranslateMatrix(objectPos);

    vector<vec3> positions = {
        newPos.Transform(mat4::RotationMatrix(-60) * mat),
        newPos.Transform(mat4::RotationMatrix(180) * mat),
        newPos.Transform(mat4::RotationMatrix(60) * mat),
    };

    for (size_t i = 0; i < positions.size(); i++)
    {
        if (vec2(positions[i]).Round() == vec2(pos).Round())
            return i;
    }

    return -1;
}

void TriangleToSquarePoints::ConvertZoneId(int zoneId, TriangleZones &zone, HeightZones &height)
{
    height = static_cast<HeightZones>(zoneId / 3);
    zone = static_cast<TriangleZones>(zoneId % 3);
}

ConnectionTypes TriangleToSquarePoints::GetTypeByZone(int zoneId)
{
    return ConnectionTypes::Independent;
}