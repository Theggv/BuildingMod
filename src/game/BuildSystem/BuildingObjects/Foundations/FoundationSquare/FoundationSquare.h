#ifndef _BUILDINGOBJECTS_FOUNDATIONSQUARE_
#define _BUILDINGOBJECTS_FOUNDATIONSQUARE_

#include <pch.h>
#include "../FoundationBase.h"

enum class SquareZones
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
};

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 * 		RendererComponent
 * 		IColliderComponent
 * 		StabilityComponent
 * 		SquareZoneComponent
 * */
class FoundationSquare : public FoundationBase
{
public:
	FoundationSquare(edict_t *owner);

	virtual void OnStart() override;

protected:
	virtual AimTestResult TraceGroundTest(AimTestResult &result) override;
	virtual AimTestResult AimTest(ray ray) override;

	virtual Shape GetShape(AimTestResult result);

private:
};

#endif // !_BUILDINGOBJECTS_FOUNDATIONSQUARE_
