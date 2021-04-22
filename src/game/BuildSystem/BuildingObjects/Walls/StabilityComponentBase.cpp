#include "StabilityComponentBase.h"
#include <game/BuildSystem/ConnectionManager.h>
#include <iostream>

using namespace WallBaseResolvers;

void StabilityComponentBase::CalculateStability(int cycle)
{
	// prevent random loop recursion
	if (cycle >= 100)
		return;

	// Find parent with highest stability
	auto parents = ConnectionManager::Instance().GetParents(m_Parent);

	double parentStability = 0.0;
	double parentCoef = 0.7;

	for (auto link : parents)
	{
		// All links should be valid, but check for safety
		if (link.second.expired())
			continue;

		auto object = *link.second.lock();

		auto stability = object->GetComponent<IStabilityComponent>();

		// Check is object has stability component, for safety ofc
		if (stability == nullptr)
			continue;

		if (stability->GetStability() > parentStability ||
			parentStability == 0.0)
			parentStability = stability->GetStability();
	}

	auto additionals = ConnectionManager::Instance().GetAdditionals(m_Parent);

	double additionalStability = 0.0;
	double additionalCoef = 0.1;

	for (auto link : additionals)
	{
		// All links should be valid, but check for safety
		if (link.second.expired())
			continue;

		auto object = *link.second.lock();

		auto stability = object->GetComponent<IStabilityComponent>();

		// Check is object has stability component, for safety ofc
		if (stability == nullptr)
			continue;

		additionalStability += stability->GetStability() * additionalCoef;
	}

	auto newStability = parentStability * parentCoef + additionalStability;

	// It can't be possible, but for sure
	if (newStability > 1.0)
		newStability = 1.0;

	// eps check
	if (fabs(newStability - m_Stability) < 1e-6)
		return;

	m_Stability = newStability;

	UpdateDependentObjects(cycle + 1);
}