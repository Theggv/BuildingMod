#ifndef _BUILDOBJECTS_SQUAREZONECOMPONENT_
#define _BUILDOBJECTS_SQUAREZONECOMPONENT_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/Components/TriggerZoneComponent.h>
#include <game/BuildSystem/BuildObjects/FoundationBase/FoundationBase.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

using namespace std;

enum class SquareZones
{
    RIGHT,
    DOWN,
    LEFT,
    UP,
};

class SquareZoneComponent : public TriggerZoneComponent
{
public:
    SquareZoneComponent();

    void AddConnection(GameObject *object) override;

protected:
    void GenerateZones() override;
    vector<Triangle> GetTransformedZone(GameObject *object, int zoneId) override;

private:
    p_GameObjectWeak_t m_Connections[4];

    bool HasConnection(SquareZones squareZone);

    SquareZones GetZoneById(int zoneId);
    HeightZones GetHeightById(int zoneId);
    int GetZoneId(int zone, int height);

    vector<Triangle> GenerateZone(int zoneId);
};

#endif // !_BUILDOBJECTS_SQUAREZONECOMPONENT_
