#ifndef _BUILDOBJECTS_FOUNATIONSQUARE_FOUNDATIONRESOLVER_
#define _BUILDOBJECTS_FOUNATIONSQUARE_FOUNDATIONRESOLVER_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include "../../FoundationSquare.h"

using namespace std;

namespace FoundationSquareResolvers
{
    class FoundationResolver : public IObjectResolver
    {
    public:
        FoundationResolver();

        virtual bool CanResolve(GameObject *object, GameObject *bindable) override;

    protected:
        void GenerateZones() override;
        vector<Triangle> GetTransformedZone(GameObject *object, int zoneId) override;

    private:
        bool HasConnection(SquareZones squareZone);

        SquareZones GetZoneById(int zoneId);
        HeightZones GetHeightById(int zoneId);
        int GetZoneId(int zone, int height);

        vector<Triangle> GenerateZone(int zoneId);
    };
}

#endif // !_BUILDOBJECTS_FOUNATIONSQUARE_FOUNDATIONRESOLVER_
