#include "GameObjectFactory.h"

// Game objects
#include <game/BuildSystem/BuildingObjects/FoundationSquare/FoundationSquare.h>
#include <game/BuildSystem/BuildingObjects/FoundationTriangle/FoundationTriangle.h>
#include <game/BuildSystem/BuildingObjects/WallFull/WallFull.h>

GameObject *GameObjectFactory::CreateFoundationSquare(edict_t *owner)
{
    return new FoundationSquare(owner);
}

GameObject *GameObjectFactory::CreateFoundationTriangle(edict_t *owner)
{
    return new FoundationTriangle(owner);
}

GameObject *GameObjectFactory::CreateWall(edict_t *owner)
{
    return new WallFull(owner);
}