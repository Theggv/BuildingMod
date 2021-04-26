#ifndef _BUILDINGOBJECTS_WALLBASE_STABILITYCOMPONENTBASE_
#define _BUILDINGOBJECTS_WALLBASE_STABILITYCOMPONENTBASE_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace std;

namespace WallBaseResolvers
{
	class StabilityComponentBase : public IStabilityComponent
	{
	public:
		virtual void CalculatePrimaryStability() override;
		virtual void CalculateSecondaryStability(int cycle = 0) override;
	};
}

#endif // !_BUILDINGOBJECTS_WALLBASE_STABILITYCOMPONENTBASE_
