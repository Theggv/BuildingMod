#ifndef _BUILDINGOBJECTS_FOUNDATIONBASE_
#define _BUILDINGOBJECTS_FOUNDATIONBASE_

#include <pch.h>
#include <Utility/AimTestResult.h>
#include <game/BuildSystem/BuildingObjects/BuildingObject.h>
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
class FoundationBase : public BuildingObject
{
public:
    FoundationBase(edict_t *owner);

    virtual void OnStart() override;
    virtual void OnUpdate() override;
    virtual void OnStateUpdated() override;

    static const double m_ModelSize;

protected:
    static const double m_MinHeight;
    static const double m_MaxHeight;

    virtual void AimHandler() override;

    virtual AimTestResult TraceGroundTest(AimTestResult &result) = 0;
    AimTestResult MaxHeightTest(AimTestResult aimTest, AimTestResult groundTest);
    AimTestResult MinHeightTest(AimTestResult aimTest, AimTestResult groundTest);

private:
    AimTestResult IntersectionTest(AimTestResult result);
};

#endif // !_BUILDINGOBJECTS_FOUNDATIONBASE_
