#ifndef _BUILDINGOBJECTS_FOUNATIONSQUARE_WALLRESOLVER_
#define _BUILDINGOBJECTS_FOUNATIONSQUARE_WALLRESOLVER_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>

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
        vector<Triangle> GenerateZone();

        // has only 1 zone (up)
        bool HasConnection();

        bool IsTouch(Shape s1, Shape s2);
    };
}

#endif // !_BUILDINGOBJECTS_FOUNATIONSQUARE_WALLRESOLVER_
