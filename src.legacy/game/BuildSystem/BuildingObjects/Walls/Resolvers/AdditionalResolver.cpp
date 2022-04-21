#include "AdditionalResolver.h"
#include <game/BuildSystem/ConnectionManager.h>

using namespace WallBaseResolvers;

AdditionalResolver::AdditionalResolver()
{
	GenerateZones();
}

bool AdditionalResolver::CanResolve(GameObject *object, GameObject *bindable)
{
	if (dynamic_cast<WallBase *>(object) == nullptr ||
		dynamic_cast<WallBase *>(bindable) == nullptr)
		return false;

	auto wall = dynamic_cast<WallBase *>(object);
	auto other = dynamic_cast<WallBase *>(bindable);

	return IsTouch(wall->GetShape(), other->GetShape());
}

void AdditionalResolver::GenerateZones()
{
	m_Zones.clear();
}

AimTestResult AdditionalResolver::TryConnect(ray ray, GameObject *object, GameObject *bindable)
{
	if (m_Successor != nullptr)
		return m_Successor->TryConnect(ray, object, bindable);

	return AimTestResult(false);
}

void AdditionalResolver::AddConnection(GameObject *object, GameObject *bindable)
{
	if (!CanResolve(object, bindable))
	{
		if (m_Successor != nullptr)
			m_Successor->AddConnection(object, bindable);

		return;
	}

	ConnectionManager::Instance().AddLinkAdditional(object, bindable);
}

bool AdditionalResolver::IsTouch(Shape s1, Shape s2)
{
	// Найти все точки, лежащие на одной прямой
	set<vec3, vec3> v1, v2;

	for (auto p1 : s1.GetPoints())
	{
		for (auto p2 : s2.GetPoints())
		{
			// Найти первую точку, которая соприкасается со второй
			if (vec2(p1) != vec2(p2))
				continue;

			v1.insert(p1);
			v2.insert(p2);

			// Найти вторую точку, которая имеет такие же координаты,
			// но другую высоту в первой фигуре

			for (auto p3 : s1.GetPoints())
			{
				if (p1 == p3)
					continue;

				if (vec2(p3) != vec2(p2))
					continue;

				v1.insert(p3);
			}

			// Найти вторую точку, которая имеет такие же координаты,
			// но другую высоту во второй фигуре

			for (auto p4 : s2.GetPoints())
			{
				if (p2 == p4)
					continue;

				if (vec2(p4) != vec2(p2))
					continue;

				v2.insert(p4);
			}
		}
	}

	// Найдены ли точки
	if (v1.size() != 2 && v2.size() != 2)
		return false;

	auto v1min = min((*v1.begin()).z, (*v1.rbegin()).z);
	auto v1max = max((*v1.begin()).z, (*v1.rbegin()).z);
	auto v2min = min((*v2.begin()).z, (*v2.rbegin()).z);
	auto v2max = max((*v2.begin()).z, (*v2.rbegin()).z);

	if (v2min >= v1min && v2min < v1max ||
		v1min >= v2min && v1min < v2max)
		return true;

	return false;
}
