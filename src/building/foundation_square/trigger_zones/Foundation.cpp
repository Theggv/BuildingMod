#include "Foundation.h"
#include <building/constants.h>

using namespace FoundationSquareNamespace;

TriggerZonesFoundation::TriggerZonesFoundation()
{
    GenerateZones();
}

int TriggerZonesFoundation::GetConnectionPoint(FoundationSquare *object, Ray &ray)
{
    if (!object)
        return -1;

    auto links = object->GetLinks();

    // left up right down
    std::vector<bool> flags = {false, false, false, false};

    for (auto [zoneId, link] : links)
    {
        if (link.object.expired())
            continue;

        if (!dynamic_pointer_cast<FoundationBase>(link.object.lock()))
            continue;

        flags[zoneId] = true;
    }

    std::vector<std::pair<bool, bool>> combs = {
        {flags[3], flags[1]},
        {flags[0], flags[2]},
        {flags[1], flags[3]},
        {flags[2], flags[0]}};

    double minDist = 0;
    double zoneHit = -1;

    for (int zoneId = 0; zoneId < 4; ++zoneId)
    {
        for (int height = 0; height < 3; ++height)
        {
            auto idx = PackIndex(height, zoneId, combs[zoneId].first, combs[zoneId].second);

            auto dist = this->GetDistanceToZone(object, ray, idx);

            if (!minDist || dist < minDist)
            {
                minDist = dist;
                zoneHit = this->PackZone(zoneId, height);
            }
        }
    }

    return zoneHit;
}

/**
 *
 * No neighbours |  Has left    |   Has right   |     Both
 *               |              |               |
 *   --------    |   -------    |    -------    |    ------
 *   \ zone /    |   |zone /    |    \ zone|    |    |zone|
 *    ------     |   ------     |     ------    |    ------
 *    |    |     |   |    |     |     |    |    |    |    |
 *    ------     |   ------     |     ------    |    ------
 *
 * */
std::vector<vec2>
TriggerZonesFoundation::GetZoneShape(bool hasLeftNeighbour, bool hasRightNeighbour)
{
    const double w = UNIT_SIZE / 2 + 2;
    const double u = w * 1.5;

    return std::vector<vec2>(
        {vec2(-w, w),                                  // bottom left
         hasLeftNeighbour ? vec2(-w, u) : vec2(-u, u), // top left
         hasRightNeighbour ? vec2(w, u) : vec2(u, u),  // top right
         vec2(w, w)});                                 // bottom right
}

void TriggerZonesFoundation::GenerateZones()
{
    // flag[0] = hasLeftNeighbour, flag[1] = hasRightNeighbour
    std::vector<std::vector<bool>> flags =
        {{false, false},
         {true, false},
         {false, true},
         {true, true}};

    std::vector<vec2> heights = {vec2(-128, -30), vec2(-30, 30), vec2(30, 128)};

    for (auto &flag : flags)
    {
        for (int zoneId = 0; zoneId < 4; ++zoneId)
        {
            for (int height = 0; height < 3; ++height)
            {
                auto shape = GetZoneShape(flag[0], flag[1]);
                auto triangles = Triangle::GenerateTriangles(
                    shape[0], shape[1], shape[2], shape[3], heights[height]);

                auto mat = mat4::RotationMatrix(90.0 * (zoneId - 1));

                for (size_t i = 0; i < triangles.size(); ++i)
                {
                    triangles[i] = triangles[i].Transform(mat);
                }

                m_TriggerZones.emplace_back(triangles);
            }
        }
    }
}

int TriggerZonesFoundation::PackZone(int zoneId, int height)
{
    return zoneId + height * 4;
}

std::vector<int> TriggerZonesFoundation::UnpackZone(int packedZoneId)
{
    return std::vector<int>({packedZoneId % 4, packedZoneId / 4});
}

int TriggerZonesFoundation::PackIndex(int height, int zone, bool hasLeft, bool hasRight)
{
    return ((size_t)hasRight << 1) + ((size_t)hasLeft) * 12 + zone * 3 + height;
}
