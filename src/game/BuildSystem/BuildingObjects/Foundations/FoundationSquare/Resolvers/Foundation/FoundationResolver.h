#ifndef _BUILDINGOBJECTS_FOUNATIONSQUARE_FOUNDATIONRESOLVER_
#define _BUILDINGOBJECTS_FOUNATIONSQUARE_FOUNDATIONRESOLVER_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace std;

namespace FoundationSquareResolvers
{
    class FoundationResolver : public IObjectResolver
    {
    public:
        FoundationResolver();

        virtual bool CanResolve(p_GameObject_t object, p_GameObject_t bindable) override;

    protected:
        void GenerateZones() override;
        vector<Triangle> GetTransformedZone(p_GameObject_t object, int zoneId) override;

    private:
        SquareZones GetZoneById(int zoneId);
        HeightZones GetHeightById(int zoneId);
        int GetZoneId(int zone, int height);

        vector<Triangle> GenerateZone(int zoneId);
    };
}

#endif // !_BUILDINGOBJECTS_FOUNATIONSQUARE_FOUNDATIONRESOLVER_
