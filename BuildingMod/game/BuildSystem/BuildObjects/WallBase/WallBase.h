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

    /**
     * Идея метода - соединить this фундамент с other, 
     * и затем вызвать other->ConnectionFoundations(this, false)
     * useRecursion нужна, чтобы метод не зациклился 
    * */
    virtual void ConnectFoundations(WallBase *other, bool useRecursion = true) = 0;

protected:
    static const double m_ModelSize;
    static const double m_Height;

    virtual void AimPointHandler();
    virtual AimTestResult TraceGroundTest(AimTestResult result) = 0;
    AimTestResult MaxHeightTest(AimTestResult aimTest, AimTestResult groundTest);
    AimTestResult MinHeightTest(AimTestResult aimTest, AimTestResult groundTest);

    virtual AimTestResult AimTest(ray ray) = 0;

    Shape GetShape();
    virtual Shape GetShape(AimTestResult result) = 0;

private:
    AimTestResult IntersectionTest(AimTestResult result);
};

#endif // !_BUILDOBJECTS_WALLBASE_
