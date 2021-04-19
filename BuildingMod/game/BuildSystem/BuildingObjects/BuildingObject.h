#ifndef _BUILDINGOBJECTS_BUILDINGOBJECT_
#define _BUILDINGOBJECTS_BUILDINGOBJECT_

#include <pch.h>
#include <Utility/AimTestResult.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>

class BuildingObject : public GameObject
{
public:
	BuildingObject(edict_t *owner);

protected:
	virtual void AimHandler() = 0;
	virtual AimTestResult AimTest(ray ray) = 0;

	virtual Shape GetShape();
	virtual Shape GetShape(AimTestResult result) = 0;
};

#endif // !_BUILDINGOBJECTS_BUILDINGOBJECT_
