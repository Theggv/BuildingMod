#include "ServerHooks.h"
#include <game/BuildSystem/ObjectManager.h>
#include <game/Server/FrameState.h>
#include <game/Utility/EdictFlags.h>
#include <game/Utility/Utility.h>

#ifndef MAX_PLAYERS
#define MAX_PLAYERS	32
#endif // !MAX_PLAYERS

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

	return gameObject->UpdateFullPack(false);
}

int pfnAddToFullPack_Post(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet)
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
	FrameState::Instance().SetState({state, e, ent, host, hostflags, player, pSet}, true);

	return gameObject->UpdateFullPack(true);
}

void CBasePlayer_PreThink(IReGameHook_CBasePlayer_PreThink* chain, CBasePlayer* pPlayer)
{
	if (!pPlayer->IsAlive())
	{
		chain->callOriginal(pPlayer);
		return;
	}

	int index = pPlayer->entindex();
	
	if (index < 0 || index >= MAX_PLAYERS)
	{
		chain->callOriginal(pPlayer);
		return;
	}

	// sample
	auto objectId = EdictFlags::GetPlayerSelectedObject(pPlayer->edict());

	auto &manager = ObjectManager::Instance();
	auto gameObjectPtr = manager.GetPtr(objectId).lock();

	if (gameObjectPtr != nullptr)
		(*gameObjectPtr)->Update();

	gameObjectPtr.reset();

	chain->callOriginal(pPlayer);
}

void CBasePlayer_PostThink(IReGameHook_CBasePlayer_PostThink* chain, CBasePlayer* pPlayer)
{
	if (!pPlayer->IsPlayer())
	{
		chain->callOriginal(pPlayer);
		return;
	}

	static int players[33];

	int index = pPlayer->entindex();

	players[index]++;

	if (players[index] > 25)
	{
		players[index] = 0;

		auto ptr = UTIL_GetAimingObject(index).lock();

		if (ptr == nullptr)
		{
			ptr.reset();
			chain->callOriginal(pPlayer);
			return;
		}

		auto object = *ptr;
		auto className = typeid(*object).name();

		EdictFlags::SetPlayerSelectedObject(pPlayer->edict(), object->Id);

		//char buffer[190];
		//sprintf_s(buffer, sizeof(buffer), "[%s #%d] Stability: %.0f%s Attached: %d Stability: %d Other: %d",
		//	className, object->GetIndex(), object->GetStability(), "%%", object->GetAttachedObjects().size(),
		//	object->GetStabilityObjects().size(), object->GetOtherObjects().size());

		//UTIL_ClientPrint(pPlayer->edict(), MessageDest::PrintCenter, buffer);

		ptr.reset();
	}

	chain->callOriginal(pPlayer);
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