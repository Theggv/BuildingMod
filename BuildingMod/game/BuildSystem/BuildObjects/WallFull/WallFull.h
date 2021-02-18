#ifndef _BUILDOBJECTS_WALLFULL_
#define _BUILDOBJECTS_WALLFULL_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/WallBase/WallBase.h>

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

    virtual void Start() override;

protected:
    static const double m_Height;


    virtual AimTestResult AimTest(ray ray) override;

    virtual Shape GetShape(AimTestResult result);

private:
};

#endif // !_BUILDOBJECTS_WALLFULL_
