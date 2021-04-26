#include "StabilityComponentBase.h"
#include <game/BuildSystem/ConnectionManager.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>

using namespace FoundationBaseNS;

void StabilityComponentBase::CalculatePrimaryStability()
{
	m_PrimaryStability = 1.0;
}

void StabilityComponentBase::CalculateSecondaryStability(int cycle)
{
	m_SecondaryStability = 0.0;

	auto children = ConnectionManager::Instance().GetChildren(GetParent());

	for (auto link : children)
	{
		// All links should be valid, but check for safety
		if (link.second.expired())
			continue;

		auto object = link.second.lock();

		auto stability = object->GetComponent<IStabilityComponent>();

		stability->StartCalculation();
	}

	OnStabilityCalculated();
}