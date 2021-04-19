#ifndef _BUILDINGOBJECTS_FOUNATIONSQUARE_WALLRESOLVER_
#define _BUILDINGOBJECTS_FOUNATIONSQUARE_WALLRESOLVER_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/BuildingObjects/FoundationBase/FoundationBase.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include <game/BuildSystem/BuildingObjects/FoundationSquare/FoundationSquare.h>

using namespace std;

namespace WallFullResolvers
{
    class WallResolver : public IObjectResolver
    {
    public:
        WallResolver();

        virtual bool CanResolve(GameObject *object, GameObject *bindable) override;

    protected:
        void GenerateZones() override;
        bool HasConnection(SquareZones squareZone);

        SquareZones GetZoneById(int zoneId);
        HeightZones GetHeightById(int zoneId);
        int GetZoneId(int zone, int height);

        vector<Triangle> GenerateZone(int zoneId);
    };
}

#endif // !_BUILDINGOBJECTS_FOUNATIONSQUARE_WALLRESOLVER_
