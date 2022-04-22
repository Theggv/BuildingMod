#if !defined(_INTERFACES_ITRIGGERRESOLVER_)
#define _INTERFACES_ITRIGGERRESOLVER_

#include <pch.h>
#include "BuildingObject.h"
#include "trigger_zones/ITriggerZones.h"
#include <interfaces/Position.h>
#include <interfaces/ResolverRet.h>

struct Ray;

class ITriggerResolver
{
public:
	virtual ~ITriggerResolver();

	void AddResolver(std::unique_ptr<ITriggerZones> &resolver);

	/// <summary>
	/// Try to attach object to other
	/// </summary>
	/// <param name="object">Object to attach</param>
	/// <param name="other">Object that should be attached</param>
	/// <param name="ray">Ray from the player to some point in the world</param>
	ResolverRet Resolve(BuildingObject* object, BuildingObject* other, Ray& ray);

	/// <summary>
	/// Checks if class can resolve that kind of object
	/// </summary>
	/// <param name="object">Object to attach</param>
	/// <returns></returns>
	virtual bool CanResolve(BuildingObject* object) = 0;
protected:
	std::vector<std::unique_ptr<ITriggerZones>> m_resolvers;
};

#endif // _INTERFACES_ITRIGGERRESOLVER_
