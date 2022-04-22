#include "TriggerResolver.h"
#include "FoundationSquare.h"

using namespace FoundationSquareNamespace;

TriggerResolver::TriggerResolver()
{
}

TriggerResolver::~TriggerResolver()
{
}

bool TriggerResolver::CanResolve(BuildingObject* object)
{
	if (!object || !dynamic_cast<FoundationSquare*>(object))
		return false;

	return true;
}