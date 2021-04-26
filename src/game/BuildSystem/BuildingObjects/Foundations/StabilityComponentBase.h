#ifndef _BUILDINGOBJECTS_FOUNDATIONBASE_STABILITYCOMPONENTBASE_
#define _BUILDINGOBJECTS_FOUNDATIONBASE_STABILITYCOMPONENTBASE_

#include <pch.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>

using namespace std;

namespace FoundationBaseNS
{
	class StabilityComponentBase : public IStabilityComponent
	{
	public:
		virtual void CalculatePrimaryStability() override;
		virtual void CalculateSecondaryStability(int cycle = 0) override;
	};
}

#endif // !_BUILDINGOBJECTS_FOUNDATIONBASE_STABILITYCOMPONENTBASE_
