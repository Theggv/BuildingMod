#include "WallPoints.h"
#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace WallFullResolvers;

AimTestResult WallPoints::GetConnectionPoint(
    p_GameObject_t object, p_GameObject_t bindable, int zoneId)
{
    if (dynamic_pointer_cast<WallBase>(bindable) == nullptr)
        return CallNext(object, bindable, zoneId);

    auto wall = dynamic_pointer_cast<WallBase>(object);

    vec3 newPos = vec3(0, 0, WallBase::m_ModelSize);

    vec3 pos = *wall->GetTransform()->GetPosition();
    vec3 rot = *wall->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(rot.y) *
               mat4::TranslateMatrix(pos);

    return AimTestResult(true,
                         newPos.Transform(mat),
                         rot.y);
}

int WallPoints::GetZoneIdByPosition(p_GameObject_t object, p_GameObject_t bindable, vec3 pos)
{
    if (dynamic_pointer_cast<WallBase>(bindable) == nullptr)
        return CallNext(object, bindable, pos);

    auto wall = dynamic_pointer_cast<WallBase>(object);

    vec3 newPos = vec3(0, 0, WallBase::m_ModelSize);

    vec3 objectPos = *wall->GetTransform()->GetPosition();
    vec3 objectRot = *wall->GetTransform()->GetRotation();

    mat4 mat = mat4::RotationMatrix(objectRot.y) *
               mat4::TranslateMatrix(objectPos);

    vec3 position = newPos.Transform(mat);

    if (position.Round() == pos.Round())
        return 0;

    return -1;
}

ConnectionTypes WallPoints::GetTypeByZone(int zoneId)
{
    return ConnectionTypes::Child;
}