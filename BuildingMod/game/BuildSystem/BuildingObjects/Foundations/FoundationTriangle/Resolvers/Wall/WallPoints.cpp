#include "WallPoints.h"
#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace FoundationTriangleResolvers;

AimTestResult WallPoints::GetConnectionPoint(
    GameObject *object, GameObject *bindable, int zoneId)
{
    if (dynamic_cast<WallBase *>(bindable) == nullptr)
        return CallNext(object, bindable, zoneId);

    auto foundation = dynamic_cast<FoundationTriangle *>(object);

    vec3 newPos = vec3(0, foundation->m_Height / 3, 0);

    vec3 pos = *foundation->GetTransform()->GetPosition();
    vec3 rot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(-90 - rot.y) *
               mat4::TranslateMatrix(pos);

    switch (static_cast<TriangleZones>(zoneId))
    {
    case TriangleZones::RIGHT:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(-60) * mat),
                             rot.y + 60 + 90);
    case TriangleZones::DOWN:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(180) * mat),
                             rot.y + 180 + 90);
    case TriangleZones::LEFT:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(60) * mat),
                             rot.y - 60 + 90);
    }

    return AimTestResult(false);
}

int WallPoints::GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos)
{
    if (dynamic_cast<WallBase *>(bindable) == nullptr)
        return CallNext(object, bindable, pos);

    auto foundation = dynamic_cast<FoundationTriangle *>(object);

    vec3 newPos = vec3(0, foundation->m_Height / 3, 0);

    vec3 objectPos = *foundation->GetTransform()->GetPosition();
    vec3 objectRot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(-90 - objectRot.y) *
               mat4::TranslateMatrix(objectPos);

    vector<vec3> positions = {
        newPos.Transform(mat4::RotationMatrix(-60) * mat),
        newPos.Transform(mat4::RotationMatrix(180) * mat),
        newPos.Transform(mat4::RotationMatrix(60) * mat),
    };

    for (size_t i = 0; i < positions.size(); i++)
    {
        if (positions[i].Round() == pos.Round())
            return i;
    }

    return -1;
}

ConnectionTypes WallPoints::GetTypeByZone(int zoneId)
{
    return ConnectionTypes::Child;
}