#ifndef _BUILDOBJECTS_WALLBASE_
#define _BUILDOBJECTS_WALLBASE_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/AimTestResult.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>

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

#endif // !_BUILDOBJECTS_WALLBASE_
