#ifndef _BUILDOBJECTS_FOUNDATION_
#define _BUILDOBJECTS_FOUNDATION_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>

enum class HeightZones
{
	LOW,
	MIDDLE,
	HIGH,
};

enum class FoundationZones
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Foundation : public GameObject
{
public:
	Foundation(edict_t *owner);

	virtual void Start() override;
	virtual void Update() override;
	virtual void StateUpdated() override;

protected:
	const int m_ModelSize = 112;
	const int m_MinHeight = 8;
	const int m_MaxHeight = m_ModelSize - m_MinHeight;

	virtual void AimPointHandler();
	virtual bool TraceGroundTest(Vector &viewPoint, Vector &viewAngle);
	virtual bool FoundationAimTest(ray &ray, vec3 &ownerOrigin);

	void AddConnection(GameObject *object, FoundationZones zone);
	bool HasConnection(FoundationZones zone);

private:
	p_GameObjectWeak_t m_Connections[4];

	int FoundationConnectionTest(ray &ray, Foundation *other);
	std::vector<Triangle> GetTriggerZone(FoundationZones zone, HeightZones height);

	// note: works if state is solid
	static vec3 GetConnectionPoint(Foundation *foundation, FoundationZones zone, HeightZones height);
};

#endif // !_BUILDOBJECTS_FOUNDATION_
