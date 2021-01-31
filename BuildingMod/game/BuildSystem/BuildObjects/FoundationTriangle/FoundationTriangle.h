#ifndef _BUILDOBJECTS_FOUNDATIONTRIANGLE_
#define _BUILDOBJECTS_FOUNDATIONTRIANGLE_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>

enum class TriangleZones
{
	RIGHT,
	DOWN,
	LEFT
};

class FoundationSquare;

/**
 *  Components:
 *      OwnerComponent
 *      VisualizerComponent
 * 		RendererComponent
 * 		IColliderComponent
 * 		StabilityComponent
 * */
class FoundationTriangle : public FoundationBase
{
	friend class FoundationSquare;

public:
	FoundationTriangle(edict_t *owner);

	virtual void Start() override;
	virtual void Update() override;

	void ConnectFoundations(FoundationBase *other, bool useRecursion = true) override;

protected:
	// virtual void AimPointHandler() override;
	virtual AimTestResult TraceGroundTest(AimTestResult result) override;
	virtual AimTestResult FoundationAimTest(ray ray) override;

	virtual Shape GetShape(AimTestResult result);

	void AddConnection(GameObject *object, TriangleZones zone);
	bool HasConnection(TriangleZones zone);

private:
	static const double m_Height;
	p_GameObjectWeak_t m_Connections[3];

	int FoundationConnectionTest(ray ray, FoundationSquare *other);
	int FoundationConnectionTest(ray ray, FoundationTriangle *other);
	std::vector<Triangle> GetTriggerZone(TriangleZones zone, HeightZones height);

	vec3 GetConnectionPoint(TriangleZones zone, HeightZones height, bool isForTriangle);
};

#endif // !_BUILDOBJECTS_FOUNDATIONTRIANGLE_
