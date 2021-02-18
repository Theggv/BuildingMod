#include "SquareToSquarePoints.h"

AimTestResult SquareToSquarePoints::GetConnectionPoint(
    GameObject *object, GameObject *bindable, int zoneId)
{
    if (dynamic_cast<FoundationSquare *>(bindable) == nullptr)
        return CallNext(object, bindable, zoneId);

    auto foundation = dynamic_cast<FoundationSquare *>(object);

    SquareZones squareZone;
    HeightZones heightZone;
    ConvertZoneId(zoneId, squareZone, heightZone);

    double heights[3] = {-foundation->m_ModelSize / 2.0, 0, foundation->m_ModelSize / 2.0};
    auto height = heights[static_cast<int>(heightZone)];

    vec3 newPos = vec3(0, foundation->m_ModelSize, height);

    vec3 pos = *foundation->GetTransform()->GetPosition();
    vec3 rot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(90 - rot.y) *
               mat4::TranslateMatrix(pos);

    switch (squareZone)
    {
    case SquareZones::RIGHT:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(90) * mat),
                             rot.y - 90);
    case SquareZones::DOWN:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(180) * mat),
                             rot.y + 180);
    case SquareZones::LEFT:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(-90) * mat),
                             rot.y + 90);
    case SquareZones::UP:

        return AimTestResult(true,
                             newPos.Transform(mat),
                             rot.y);

    default:
        return AimTestResult(false);
    }
}

int SquareToSquarePoints::GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos)
{
    if (dynamic_cast<FoundationSquare *>(bindable) == nullptr)
        return CallNext(object, bindable, pos);

    auto foundation = dynamic_cast<FoundationSquare *>(object);

    vec3 newPos = vec3(0, foundation->m_ModelSize, 0);

    vec3 objectPos = *foundation->GetTransform()->GetPosition();
    vec3 objectRot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(90 - objectRot.y) *
               mat4::TranslateMatrix(objectPos);

    vector<vec3> positions = {
        newPos.Transform(mat4::RotationMatrix(90) * mat),
        newPos.Transform(mat4::RotationMatrix(180) * mat),
        newPos.Transform(mat4::RotationMatrix(-90) * mat),
        newPos.Transform(mat),
    };

    for (size_t i = 0; i < positions.size(); i++)
    {
        if (vec2(positions[i]).Round() == vec2(pos).Round())
            return i;
    }

    return -1;
}

void SquareToSquarePoints::ConvertZoneId(int zoneId, SquareZones &zone, HeightZones &height)
{
    height = static_cast<HeightZones>(zoneId / 4);
    zone = static_cast<SquareZones>(zoneId % 4);
}