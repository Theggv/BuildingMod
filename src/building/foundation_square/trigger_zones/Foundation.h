#if !defined(_FOUNDATION_SQUARE_TRIGGER_ZONES_FOUNDATION_H)
#define _FOUNDATION_SQUARE_TRIGGER_ZONES_FOUNDATION_H

#include <pch.h>

#include <math/math_include.h>
#include <building/base/trigger_zones/ITriggerZones.h>
#include <interfaces/Position.h>
#include "../ConnectionPoints.h"
#include "../FoundationSquare.h"

namespace FoundationSquareNamespace
{
    class TriggerZonesFoundation : public ITriggerZones
    {
    public:
        TriggerZonesFoundation();
        ~TriggerZonesFoundation();

        /**
         * Запаковать индексы зоны и высоты в один
         * */
        int PackZone(int zoneId, int height);

        /**
         * Разпаковать индекс
         *
         * return [zoneId, height]
         * */
        std::vector<int> UnpackZone(int packedZoneId);

        /**
         * Трассировка луча в отношении объекта
         *
         * ptr - объект, на который смотрит игрок
         * ray - луч, описывающий взгляд игрока
         *
         * returns Зона, на которую игрок смотрит
         * */
        int GetConnectionPoint(FoundationSquare *object, Ray &ray);

    private:
        std::vector<std::vector<Triangle>> m_TriggerZones;

        std::vector<vec2> GetZoneShape(bool hasLeftNeighbour, bool hasRightNeighbour);
        void GenerateZones();

        int PackIndex(int height, int zone, bool hasLeft, bool hasRight);
    };
};

#endif // _FOUNDATION_SQUARE_TRIGGER_ZONES_FOUNDATION_H
