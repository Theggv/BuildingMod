#ifndef _INCLUDE_REGAMEDLL_API_H_
#define _INCLUDE_REGAMEDLL_API_H_

#pragma once

extern IReGameApi *g_ReGameApi;
extern IReGameHookchains *g_ReGameHookchains;
extern CGameRules *g_pGameRules;
extern bool RegamedllApi_Init();

extern CGameRules *InstallGameRules(IReGameHook_InstallGameRules *chain);
extern void CSGameRules_OnRoundFreezeEnd(IReGameHook_CSGameRules_OnRoundFreezeEnd *chain);
extern void CBasePlayer_Spawn(IReGameHook_CBasePlayer_Spawn *chain, CBasePlayer *pthis);
extern void CBasePlayer_TraceAttack(IReGameHook_CBasePlayer_TraceAttack *chain, CBasePlayer *pthis, entvars_t *pevAttacker, float flDamage, Vector& vecDir, TraceResult *ptr, int bitsDamageType);
extern void RadiusFlash_TraceLine(IReGameHook_RadiusFlash_TraceLine *chain, CBasePlayer *pPlayer, entvars_t *pevInflictor, entvars_t *pevAttacker, Vector& vecSrc, Vector& vecSpot, TraceResult *ptr);
extern bool InternalCommand(IReGameHook_InternalCommand* chain, edict_t* pEdict, const char* msg);
extern void SV_SendServerinfo(IRehldsHook_SV_SendServerinfo* chain, sizebuf_t* buf, IGameClient* client);
extern void HandleNetCommand(IRehldsHook_HandleNetCommand* chain, IGameClient* client, int8 a);

#endif //_INCLUDE_REGAMEDLL_API_H_
