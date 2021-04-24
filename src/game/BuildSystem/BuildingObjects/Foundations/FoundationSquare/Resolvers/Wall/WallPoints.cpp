#include "WallPoints.h"

#include <game/BuildSystem/BuildingObjects/Foundations/Foundations.h>
#include <game/BuildSystem/BuildingObjects/Walls/WallBase.h>

using namespace FoundationSquareResolvers;

AimTestResult WallPoints::GetConnectionPoint(
    p_GameObject_t object, p_GameObject_t bindable, int zoneId)
{
    if (dynamic_pointer_cast<WallBase>(bindable) == nullptr)
        return CallNext(object, bindable, zoneId);

    auto foundation = dynamic_pointer_cast<FoundationSquare>(object);

    vec3 newPos = vec3(foundation->m_ModelSize / 2, 0, 0);

    vec3 pos = *foundation->GetTransform()->GetPosition();
    vec3 rot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(rot.y) *
               mat4::TranslateMatrix(pos);

    switch (static_cast<SquareZones>(zoneId))
    {
    case SquareZones::RIGHT:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(0) * mat),
                             rot.y);
    case SquareZones::DOWN:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(-90) * mat),
                             rot.y - 90);
    case SquareZones::LEFT:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(180) * mat),
                             rot.y + 180);
    case SquareZones::UP:

        return AimTestResult(true,
                             newPos.Transform(mat4::RotationMatrix(90) * mat),
                             rot.y + 90);
    }

    return AimTestResult(false);
}

int WallPoints::GetZoneIdByPosition(p_GameObject_t object, p_GameObject_t bindable, vec3 pos)
{
    if (dynamic_pointer_cast<WallBase>(bindable) == nullptr)
        return CallNext(object, bindable, pos);

    auto foundation = dynamic_pointer_cast<FoundationSquare>(object);

    vec3 newPos = vec3(foundation->m_ModelSize / 2, 0, 0);

    vec3 objectPos = *foundation->GetTransform()->GetPosition();
    vec3 objectRot = *foundation->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(objectRot.y) *
               mat4::TranslateMatrix(objectPos);

    vector<vec3> positions = {
        newPos.Transform(mat4::RotationMatrix(0) * mat),
        newPos.Transform(mat4::RotationMatrix(-90) * mat),
        newPos.Transform(mat4::RotationMatrix(180) * mat),
        newPos.Transform(mat4::RotationMatrix(90) * mat),
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
