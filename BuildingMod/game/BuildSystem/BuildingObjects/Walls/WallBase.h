#ifndef _BUILDINGOBJECTS_WALLBASE_
#define _BUILDINGOBJECTS_WALLBASE_

#include <pch.h>
#include <game/BuildSystem/BuildingObjects/BuildingObject.h>
#include <game/BuildSystem/ObjectManager.h>
#include <Utility/AimTestResult.h>

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 *      StabilityComponent
 * */
class WallBase : public BuildingObject
{
public:
    WallBase(edict_t *owner);

    virtual void OnStart() override;
    virtual void OnUpdate() override;
    virtual void OnStateUpdated() override;

    void Connect(GameObject *other) override;

    static const double m_ModelSize;

protected:
    virtual void AimHandler() override;

private:
    AimTestResult IntersectionTest(AimTestResult result);
};

#endif // !_BUILDINGOBJECTS_WALLBASE_
