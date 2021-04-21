#include "AdditionalResolver.h"

// point generators
// #include "WallPoints.h"

using namespace WallsResolvers;

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

	return true;
}

void AdditionalResolver::GenerateZones()
{
	m_Zones.clear();
}

AimTestResult AdditionalResolver::TryConnect(ray ray, GameObject *object, GameObject *bindable)
{
	return AimTestResult(false);
}

void AdditionalResolver::AddConnection(GameObject *object, GameObject *bindable)
{
}