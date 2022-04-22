#if !defined(_FOUNDATION_SQUARE_TRIGGER_ZONES_FOUNDATION_H)
#define _FOUNDATION_SQUARE_TRIGGER_ZONES_FOUNDATION_H

#include <pch.h>

#include <math/math_include.h>
#include <building/base/trigger_zones/ITriggerZones.h>
#include "../ConnectionPoints.h"
#include "../FoundationSquare.h"

namespace FoundationSquareNamespace
{
	class TriggerZonesFoundation : public ITriggerZones
	{
	public:
		TriggerZonesFoundation();
		~TriggerZonesFoundation();

		bool CanResolve(BuildingObject* object, BuildingObject* other) override;

		ResolverRet GetConnectionPoint(BuildingObject* object, Ray& ray) override;

	private:
		std::unique_ptr<ConnectionPoints> m_ConnPoints;

		/// <summary>
		/// Pack zoneId and height to one index
		/// </summary>
		/// <param name="zoneId"></param>
		/// <param name="height"></param>
		/// <returns>Packed zone index</returns>
		int PackZone(int zoneId, int height);

		/// <summary>
		/// Unpack zone index
		/// </summary>
		/// <param name="packedZoneId">packed zone index</param>
		/// <returns>array [zoneId, height]</returns>
		std::vector<int> UnpackZone(int packedZoneId);

		std::vector<vec2> GetZoneShape(bool hasLeftNeighbour, bool hasRightNeighbour);
		void GenerateZones();

		int PackIndex(int height, int zone, bool hasLeft, bool hasRight);
	};
};

#endif // _FOUNDATION_SQUARE_TRIGGER_ZONES_FOUNDATION_H
