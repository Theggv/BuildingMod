#ifndef _BUILDINGOBJECTS_FOUNDATIONBASE_
#define _BUILDINGOBJECTS_FOUNDATIONBASE_

#include <pch.h>
#include <Utility/AimTestResult.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>

enum class HeightZones
{
    LOW,
    MIDDLE,
    HIGH,
};

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 * */
class FoundationBase : public GameObject
{
public:
    FoundationBase(edict_t *owner);

    virtual void OnStart() override;
    virtual void OnUpdate() override;
    virtual void OnStateUpdated() override;

    void Connect(GameObject *other) override;

    static const double m_ModelSize;

protected:
    static const double m_MinHeight;
    static const double m_MaxHeight;

    virtual void AimPointHandler();
    virtual AimTestResult TraceGroundTest(AimTestResult &result) = 0;
    AimTestResult MaxHeightTest(AimTestResult aimTest, AimTestResult groundTest);
    AimTestResult MinHeightTest(AimTestResult aimTest, AimTestResult groundTest);

    /**
     * return: New position if test passed, old position otherwise
     * */
    virtual AimTestResult FoundationAimTest(ray ray) = 0;

    Shape GetShape();
    virtual Shape GetShape(AimTestResult result) = 0;

private:
    AimTestResult IntersectionTest(AimTestResult result);
};

#endif // !_BUILDINGOBJECTS_FOUNDATIONBASE_
