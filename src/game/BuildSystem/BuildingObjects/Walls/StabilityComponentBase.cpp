#include "StabilityComponentBase.h"
#include <game/BuildSystem/ConnectionManager.h>
#include <game/BuildSystem/BuildingObjects/BuildingObject.h>

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

	// Get unique points
	vector<vec3> uniquePoints;

	for (auto point : dynamic_cast<WallBase *>(m_Parent)->GetShape().GetPoints())
	{
		bool isUnique = true;
		for (auto p : uniquePoints)
		{
			if (vec2(p) == vec2(point))
				isUnique = false;
		}

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

		auto object = *link.second.lock();

		auto stability = object->GetComponent<IStabilityComponent>();

		// Check is object has stability component, for safety ofc
		if (stability == nullptr)
			continue;

		for (auto point : dynamic_cast<BuildingObject *>(object)->GetShape().GetPoints())
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

	auto newStability = parentStability * parentCoef;

	for (auto stab : additionalStability)
		newStability += stab * additionalCoef;

	// It can't be possible, but for sure
	if (newStability > 1.0)
		newStability = 1.0;

	// eps check
	if (fabs(newStability - m_Stability) < 1e-6)
		return;

	m_Stability = newStability;

	UpdateDependentObjects(cycle + 1);
}