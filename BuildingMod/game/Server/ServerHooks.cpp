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

	return 1;
}

int pfnAddToFullPack_Post(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet)
{
	return 0;

	if (player)
		return 0;

	FrameState::Instance().SetState({ state, e, ent, host, hostflags, player, pSet }, true);
}

int SV_CreatePacketEntities(IRehldsHook_SV_CreatePacketEntities* chain, sv_delta_s type, IGameClient* client, packet_entities_s* to, sizebuf_s* msg)
{
	return chain->callOriginal(type, client, to, msg);

	auto host = client->GetEdict();

	for (int i = 0; i < to->num_entities; ++i)
	{
		auto state = to->entities + i;
		auto entIndex = state->number;
	}

	return chain->callNext(type, client, to, msg);
}