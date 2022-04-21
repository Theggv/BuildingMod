#ifndef _BUILDINGOBJECTS_FOUNDATIONTRIANGLE_
#define _BUILDINGOBJECTS_FOUNDATIONTRIANGLE_

#include <pch.h>
#include "../FoundationBase.h"

class FoundationSquare;

enum class TriangleZones
{
    RIGHT,
    DOWN,
    LEFT,
};

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

	virtual void OnStart() override;
	virtual void OnUpdate() override;
	// virtual int OnUpdateFullPack(bool isPost) override;

	static const double m_Height;

protected:
	virtual AimTestResult TraceGroundTest(AimTestResult &result) override;
	virtual AimTestResult AimTest(ray ray) override;

	virtual Shape GetShape(AimTestResult result);

private:
};

#endif // !_BUILDINGOBJECTS_FOUNDATIONTRIANGLE_
