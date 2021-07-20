#ifndef _BUILDINGOBJECTS_DOORFRAME_
#define _BUILDINGOBJECTS_DOORFRAME_

#include <pch.h>
#include "../WallBase.h"

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 *      StabilityComponent
 * */
class DoorFrame : public WallBase
{
public:
    DoorFrame(edict_t *owner);

    virtual void OnStart() override;

protected:
    static const double m_Height;

    virtual AimTestResult AimTest(ray ray) override;

    virtual Shape GetShape(AimTestResult result);

private:
};

#endif // !_BUILDINGOBJECTS_DOORFRAME_
