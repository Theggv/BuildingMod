#include "GameObjectFactory.h"

// Game objects
#include <game/BuildSystem/BuildingObjects/Objects.h>
#include <game/BuildSystem/ObjectManager.h>

p_GameObject_t GameObjectFactory::CreateFoundationSquare(edict_t *owner)
{
    auto object = new FoundationSquare(owner);
    return ObjectManager::Instance().Get(object->Id);
}

p_GameObject_t GameObjectFactory::CreateFoundationTriangle(edict_t *owner)
{
    auto object = new FoundationTriangle(owner);
    return ObjectManager::Instance().Get(object->Id);
}

p_GameObject_t GameObjectFactory::CreateWall(edict_t *owner)
{
    auto object = new WallFull(owner);
    return ObjectManager::Instance().Get(object->Id);
}

p_GameObject_t GameObjectFactory::AddToManager(p_GameObject_t ptr)
{
    return ptr;
    // return ObjectManager::Instance().Add(ptr);
}
