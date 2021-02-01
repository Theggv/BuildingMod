#ifndef _BUILDOBJECTS_TRIANGLEZONECOMPONENT_
#define _BUILDOBJECTS_TRIANGLEZONECOMPONENT_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/Components/TriggerZoneComponent.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

using namespace std;

enum class TriangleZones
{
    RIGHT,
    DOWN,
    LEFT,
};

class TriangleZoneComponent : public TriggerZoneComponent
{
public:
    TriangleZoneComponent();

    void AddConnection(GameObject *object) override;

protected:
    void GenerateZones() override;
    vector<Triangle> GetTransformedZone(GameObject *object, int zoneId) override;

private:
    p_GameObjectWeak_t m_Connections[3];

    bool HasConnection(TriangleZones squareZone);

    TriangleZones GetZoneById(int zoneId);
    HeightZones GetHeightById(int zoneId);
    int GetZoneId(int zone, int height);

    vector<Triangle> GenerateZone(int zoneId);
};

#endif // !_BUILDOBJECTS_TRIANGLEZONECOMPONENT_
