#include "ServerHooks.h"

int pfnAddToFullPack_Pre(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet)
{
	// Skip if ent is player
	if (player)
		return 0;

	static ObjectManager* manager;

	if (manager == nullptr)
		manager = &ObjectManager::Instance();

	auto gameObjectPtr = manager->GetPtrByEdict(ent).lock();
	
	// Skip if ent is not gameobject
	if (gameObjectPtr == nullptr)
	{
		gameObjectPtr.reset();
		return 0;
	}

	auto gameObject = *gameObjectPtr;
	gameObjectPtr.reset();

	// Save state 
	FrameState::Instance().SetState({state, e, ent, host, hostflags, player, pSet}, false);

	gameObject->UpdateFullPack(false);
}

int pfnAddToFullPack_Post(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet)
{
	return 0;

	if (player)
		return 0;

	FrameState::Instance().SetState({ state, e, ent, host, hostflags, player, pSet }, true);
}