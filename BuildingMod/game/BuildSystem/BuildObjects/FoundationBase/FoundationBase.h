#ifndef _BUILDOBJECTS_FOUNDATIONBASE_
#define _BUILDOBJECTS_FOUNDATIONBASE_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/AimTestResult.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
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

    virtual void Start() override;
    virtual void Update() override;
    virtual void StateUpdated() override;

    void ConnectFoundations(FoundationBase *other);

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

#endif // !_BUILDOBJECTS_FOUNDATIONBASE_
