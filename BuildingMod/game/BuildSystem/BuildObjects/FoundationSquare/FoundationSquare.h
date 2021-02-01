#ifndef _BUILDOBJECTS_FOUNDATIONSQUARE_
#define _BUILDOBJECTS_FOUNDATIONSQUARE_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>

class FoundationTriangle;

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
	friend class FoundationTriangle;

public:
	FoundationSquare(edict_t *owner);

	virtual void Start() override;
	virtual void StateUpdated() override;

protected:
	virtual AimTestResult TraceGroundTest(AimTestResult result) override;
	virtual AimTestResult FoundationAimTest(ray ray) override;

	virtual Shape GetShape(AimTestResult result);

private:
};

#endif // !_BUILDOBJECTS_FOUNDATIONSQUARE_
