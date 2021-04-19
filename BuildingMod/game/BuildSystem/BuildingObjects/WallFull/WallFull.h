#ifndef _BUILDINGOBJECTS_WALLFULL_
#define _BUILDINGOBJECTS_WALLFULL_

#include <pch.h>
#include <game/BuildSystem/BuildingObjects/WallBase/WallBase.h>

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 *      StabilityComponent
 * */
class WallFull : public WallBase
{
public:
    WallFull(edict_t *owner);

    virtual void OnStart() override;

protected:
    static const double m_Height;


    virtual AimTestResult AimTest(ray ray) override;

    virtual Shape GetShape(AimTestResult result);

private:
};

#endif // !_BUILDINGOBJECTS_WALLFULL_
