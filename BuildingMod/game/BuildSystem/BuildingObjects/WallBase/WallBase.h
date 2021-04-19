#ifndef _BUILDINGOBJECTS_WALLBASE_
#define _BUILDINGOBJECTS_WALLBASE_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>
#include <Utility/AimTestResult.h>

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 *      StabilityComponent
 * */
class WallBase : public GameObject
{
public:
    WallBase(edict_t *owner);

    virtual void Start() override;
    virtual void Update() override;
    virtual void StateUpdated() override;

    void Connect(GameObject *other) override;

    static const double m_ModelSize;

protected:
    virtual void AimPointHandler();

    virtual AimTestResult AimTest(ray ray) = 0;

    Shape GetShape();
    virtual Shape GetShape(AimTestResult result) = 0;

private:
    AimTestResult IntersectionTest(AimTestResult result);
};

#endif // !_BUILDINGOBJECTS_WALLBASE_
