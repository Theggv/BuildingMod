#ifndef _BUILDOBJECTS_FOUNDATIONTRIANGLE_
#define _BUILDOBJECTS_FOUNDATIONTRIANGLE_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>

class FoundationSquare;

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 * 		RendererComponent
 * 		IColliderComponent
 * 		StabilityComponent
 * 		TriangleZoneComponent
 * */
class FoundationTriangle : public FoundationBase
{
	friend class FoundationSquare;

public:
	FoundationTriangle(edict_t *owner);

	virtual void Start() override;
	virtual void Update() override;

	static const double m_Height;

protected:
	// virtual void AimPointHandler() override;
	virtual AimTestResult TraceGroundTest(AimTestResult result) override;
	virtual AimTestResult FoundationAimTest(ray ray) override;

	virtual Shape GetShape(AimTestResult result);

private:
};

#endif // !_BUILDOBJECTS_FOUNDATIONTRIANGLE_
