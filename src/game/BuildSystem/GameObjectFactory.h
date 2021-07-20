#ifndef _BUILDSYSTEM_GAMEOBJECTFACTORY_
#define _BUILDSYSTEM_GAMEOBJECTFACTORY_

#include <pch.h>

#include <game/BuildSystem/GameObject.h>

class GameObjectFactory
{
public:
    p_GameObject_t CreateFoundationSquare(edict_t *owner);
    p_GameObject_t CreateFoundationTriangle(edict_t *owner);
    p_GameObject_t CreateWall(edict_t *owner);
    p_GameObject_t CreateDoorFrame(edict_t *owner);
};

#endif // !_BUILDSYSTEM_GAMEOBJECTFACTORY_
