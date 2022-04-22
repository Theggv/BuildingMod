#if !defined(_BASE_ITRIGGERZONES_)
#define _BASE_ITRIGGERZONES_

#include <pch.h>
#include <math/math_include.h>
#include <interfaces/ResolverRet.h>

class BuildingObject;

class ITriggerZones
{
public:
	virtual ~ITriggerZones();

	/// <summary>
	/// Checks if class can resolve that kind of objects
	/// </summary>
	/// <param name="object">Object to attach</param>
	/// <param name="other">Object that should be attached</param>
	/// <returns></returns>
	virtual bool CanResolve(BuildingObject* object, BuildingObject* other) = 0;

	/// <summary>
	/// Ray tracing to the object
	/// </summary>
	/// <param name="object">Object that the player looking at</param>
	/// <param name="ray">Ray from the player to some point in the world</param>
	/// <returns>Relative position of connection point</returns>
	virtual ResolverRet GetConnectionPoint(BuildingObject* object, Ray& ray) = 0;

	/// <summary>
	/// Get a distance to the zone
	/// </summary>
	/// <param name="object"></param>
	/// <param name="ray"></param>
	/// <param name="packedIndex">Packed index of zone</param>
	/// <param name="minRayLength">Minimum trigger distance</param>
	/// <returns>dinstance^2 or 0 if no hit</returns>
	virtual double GetDistanceToZone(
		BuildingObject* object, Ray ray, int packedIndex, int minRayLength = 75);

protected:
	virtual std::vector<Triangle> GetTransformedZone(BuildingObject* object, int packedIndex);

	std::vector<std::vector<Triangle>> m_TriggerZones;
};

#endif // _BASE_ITRIGGERZONES_
