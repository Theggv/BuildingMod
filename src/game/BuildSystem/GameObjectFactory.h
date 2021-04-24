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

private:
    p_GameObject_t AddToManager(p_GameObject_t ptr);
};

#endif // !_BUILDSYSTEM_GAMEOBJECTFACTORY_
