#ifndef _BUILDOBJECTS_FOUNDATIONSQUARE_
#define _BUILDOBJECTS_FOUNDATIONSQUARE_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>

enum class SquareZones
{
	RIGHT,
	DOWN,
	LEFT,
	UP
};

class FoundationTriangle;

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 * 		RendererComponent
 * 		IColliderComponent
 * 		StabilityComponent
 * */
class FoundationSquare : public FoundationBase
{
	friend class FoundationTriangle;

public:
	FoundationSquare(edict_t *owner);

	virtual void Start() override;
	virtual void StateUpdated() override;
	
	void ConnectFoundations(FoundationBase *other, bool useRecursion = true) override;

protected:
	virtual AimTestResult TraceGroundTest(AimTestResult result) override;
	virtual AimTestResult FoundationAimTest(ray ray) override;

    virtual Shape GetShape(AimTestResult result);

	void AddConnection(GameObject *object, SquareZones zone);
	bool HasConnection(SquareZones zone);

private:
	p_GameObjectWeak_t m_Connections[4];

	int FoundationConnectionTest(ray ray, FoundationTriangle *other);
	int FoundationConnectionTest(ray ray, FoundationSquare *other);
	std::vector<Triangle> GetTriggerZone(SquareZones zone, HeightZones height);

	// note: works if state is solid
	vec3 GetConnectionPoint(SquareZones zone, HeightZones height, bool isForTriangle);
};

#endif // !_BUILDOBJECTS_FOUNDATIONSQUARE_
