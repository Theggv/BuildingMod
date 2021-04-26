#include "StabilityComponentBase.h"
#include <game/BuildSystem/ConnectionManager.h>
#include <game/BuildSystem/BuildingObjects/BuildingObject.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>

using namespace WallBaseResolvers;

void StabilityComponentBase::CalculatePrimaryStability()
{
	// Find parent with highest stability
	auto parents = ConnectionManager::Instance().GetParents(GetParent());

	double parentStability = 0.0;
	double parentCoef = 0.7;

	for (auto link : parents)
	{
		// All links should be valid, but check for safety
		if (link.second.expired())
			continue;

		auto object = link.second.lock();

		auto stability = object->GetComponent<IStabilityComponent>();

		// Check is object has stability component, for safety ofc
		if (stability == nullptr)
			continue;

		if (stability->GetStability() > parentStability ||
			parentStability == 0.0)
			parentStability = stability->GetStability();
	}

	parentStability *= parentCoef;

	// eps check
	if (fabs(parentStability - m_PrimaryStability) < 1e-6)
		return;

	m_PrimaryStability = parentStability;
	m_IsRecalcRequired = true;
}

void StabilityComponentBase::CalculateSecondaryStability(int cycle)
{
	// prevent random loop recursion
	if (cycle >= 50)
		return;

	auto additionals = ConnectionManager::Instance().GetAdditionals(GetParent());

	// Get unique points
	vector<vec3> uniquePoints;

	for (auto point : dynamic_pointer_cast<BuildingObject>(GetParent())->GetShape().GetPoints())
	{
		bool isUnique = true;
		for (auto p : uniquePoints)
			if (vec2(p) == vec2(point))
				isUnique = false;

		if (isUnique)
			uniquePoints.push_back(point);
	}

	vector<double> additionalStability(uniquePoints.size());
	double additionalCoef = 0.1;

	for (auto link : additionals)
	{
		// All links should be valid, but check for safety
		if (link.second.expired())
			continue;

		auto object = link.second.lock();

		auto stability = object->GetComponent<IStabilityComponent>();

		// Check is object has stability component, for safety ofc
		if (stability == nullptr)
			continue;

		for (auto point : dynamic_pointer_cast<BuildingObject>(object)->GetShape().GetPoints())
		{
			bool handled = false;

			for (size_t i = 0; i < uniquePoints.size(); ++i)
			{
				if (vec2(point) == vec2(uniquePoints[i]))
				{
					additionalStability[i] = max(additionalStability[i], stability->GetStability());
					handled = true;
					break;
				}
			}

			if (handled)
				break;
		}
	}

	double newStability = 0;

	for (auto stab : additionalStability)
		newStability += stab * additionalCoef;

	// eps check
	if (fabs(newStability - m_SecondaryStability) >= 1e-6 || m_IsRecalcRequired)
	{
		// Recalculate other additionals
		m_SecondaryStability = newStability;
		m_IsRecalcRequired = false;

		for (auto link : additionals)
		{
			// All links should be valid, but check for safety
			if (link.second.expired())
				continue;

			auto object = link.second.lock();

			auto stability = object->GetComponent<IStabilityComponent>();

			stability->CalculateSecondaryStability(cycle + 1);
		}

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
	}

	OnStabilityCalculated();
}