#include "WallPoints.h"
#include <game/BuildSystem/BuildObjects/FoundationSquare/FoundationSquare.h>
#include <game/BuildSystem/BuildObjects/WallBase/WallBase.h>

AimTestResult WallPoints::GetConnectionPoint(
    GameObject *object, GameObject *bindable, int zoneId)
{
    if (dynamic_cast<WallBase *>(bindable) == nullptr)
        return CallNext(object, bindable, zoneId);

    auto foundation = dynamic_cast<FoundationSquare *>(object);

    double heights[3] = {-foundation->m_ModelSize / 2.0, 0, foundation->m_ModelSize / 2.0};
    auto height = heights[zoneId];

    vec3 newPos = vec3(0, foundation->m_ModelSize / 2, height);

    vec3 pos = *foundation->GetTransform()->GetPosition();
    vec3 rot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(90 - rot.y) *
               mat4::TranslateMatrix(pos);

    switch (static_cast<SquareZones>(zoneId))
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
                             newPos.Transform(mat4::RotationMatrix(0) * mat),
                             rot.y);
    }

    return AimTestResult(false);
}

int WallPoints::GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos)
{
    if (dynamic_cast<FoundationSquare *>(bindable) == nullptr)
        return CallNext(object, bindable, pos);

    auto foundation = dynamic_cast<FoundationSquare *>(object);

    vec3 newPos = vec3(0, foundation->m_ModelSize, pos.z);

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
        if (positions[i].Round() == pos.Round())
            return i;
    }

    return -1;
}