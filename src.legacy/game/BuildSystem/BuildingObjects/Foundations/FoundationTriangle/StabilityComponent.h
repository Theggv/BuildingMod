#ifndef _BUILDINGOBJECTS_FOUNDATIONTRIANGLE_STABILITYCOMPONENT_
#define _BUILDINGOBJECTS_FOUNDATIONTRIANGLE_STABILITYCOMPONENT_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace std;

namespace FoundationTriangleResolvers
{
	class StabilityComponent : public IStabilityComponent
	{
	public:
		StabilityComponent();

		virtual void CalculateStability(int cycle = 0) override;
	};
}

#endif // !_BUILDINGOBJECTS_FOUNDATIONTRIANGLE_STABILITYCOMPONENT_
