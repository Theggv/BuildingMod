#ifndef _BUILDSYSTEM_GAMEOBJECTFACTORY_
#define _BUILDSYSTEM_GAMEOBJECTFACTORY_

#include <pch.h>

#include <game/BuildSystem/ObjectManager.h>

class GameObjectFactory
{
public:
    GameObject* CreateFoundationSquare(edict_t *owner);
    GameObject* CreateFoundationTriangle(edict_t *owner);
    GameObject* CreateWall(edict_t *owner);
};

#endif // !_BUILDSYSTEM_GAMEOBJECTFACTORY_
