#ifndef _SERVER_SERVERHOOKS_
#define _SERVER_SERVERHOOKS_

#include <pch.h>

// Hooks should be connected in module/sdk/meta_api.cpp

void ClientConnected(IRehldsHook_ClientConnected* chain, IGameClient* pPlayer);
void SV_DropClient(IRehldsHook_SV_DropClient* chain, IGameClient* pPlayer, bool crash, const char* string);
void CBasePlayer_PreThink(IReGameHook_CBasePlayer_PreThink* chain, CBasePlayer* pPlayer);
void CBasePlayer_PostThink(IReGameHook_CBasePlayer_PostThink* chain, CBasePlayer* pPlayer);
void CBasePlayer_RoundRespawn(IReGameHook_CBasePlayer_RoundRespawn* chain, CBasePlayer* pPlayer);
int SV_CreatePacketEntities(IRehldsHook_SV_CreatePacketEntities* chain, sv_delta_s type, IGameClient* client, packet_entities_s* to, sizebuf_s* msg);

int pfnAddToFullPack_Pre(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet);
int pfnAddToFullPack_Post(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet);

#endif // !_SERVER_SERVERHOOKS_
