#include <pch.h>
// #include <game/Server/ServerHooks.h>

IReGameApi *g_ReGameApi;
IReGameHookchains *g_ReGameHookchains;
CGameRules *g_pGameRules = nullptr;

bool RegamedllApi_Init()
{
	const char *szGameDLLModule = GET_GAME_INFO(PLID, GINFO_DLL_FULLPATH);

	if (szGameDLLModule == nullptr)
	{
		SEM_PRINT("[%s]: ReGameDLL szGameDLLModule NULL.", Plugin_info.logtag);
		return false;
	}

	CSysModule *gameModule = Sys_LoadModule(szGameDLLModule);

	if (!gameModule)
	{
		SEM_PRINT("[%s]: ReGameDLL gameModule NULL.", Plugin_info.logtag);
		return false;
	}

	CreateInterfaceFn ifaceFactory = Sys_GetFactory(gameModule);

	if (!ifaceFactory)
	{
		SEM_PRINT("[%s]: ReGameDLL ifaceFactory NULL.", Plugin_info.logtag);
		return false;
	}

	int retCode = 0;

	g_ReGameApi = (IReGameApi *)ifaceFactory(VRE_GAMEDLL_API_VERSION, &retCode);

	if (!g_ReGameApi)
	{
		SEM_PRINT("[%s]: ReGameDLL error load Api.", Plugin_info.logtag);
		return false;
	}

	int majorVersion = g_ReGameApi->GetMajorVersion();
	int minorVersion = g_ReGameApi->GetMinorVersion();

	if (majorVersion != REGAMEDLL_API_VERSION_MAJOR)
	{
		SEM_PRINT("[%s]: ReGameDLL API major version mismatch; expected %d, real %d.", Plugin_info.logtag, REGAMEDLL_API_VERSION_MAJOR, majorVersion);

		// need to notify that it is necessary to update the ReGameDLL.
		if (majorVersion < REGAMEDLL_API_VERSION_MAJOR)
		{
			SEM_PRINT("[%s]: Please update the ReGameDLL up to a major version API >= %d.", Plugin_info.logtag, REGAMEDLL_API_VERSION_MAJOR);
		}

		// need to notify that it is necessary to update the module.
		else if (majorVersion > REGAMEDLL_API_VERSION_MAJOR)
		{
			SEM_PRINT("[%s]: Please update the %s up to a major version API >= %d.", Plugin_info.logtag, Plugin_info.name, majorVersion);
		}

		return false;
	}

	if (minorVersion < REGAMEDLL_API_VERSION_MINOR)
	{
		SEM_PRINT("[%s]: ReGameDLL API minor version mismatch; expected at least %d, real %d.", Plugin_info.logtag, REGAMEDLL_API_VERSION_MINOR, minorVersion);
		SEM_PRINT("[%s]: Please update the ReGameDLL up to a minor version API >= %d.", Plugin_info.logtag, REGAMEDLL_API_VERSION_MINOR);
		return false;
	}

	// g_ReGameHookchains = g_ReGameApi->GetHookchains();
	// g_ReGameHookchains->InstallGameRules()->registerHook(&InstallGameRules, HC_PRIORITY_DEFAULT);

	// // UserHooks.h
	// g_ReGameHookchains->CBasePlayer_PreThink()->registerHook(&CBasePlayer_PreThink, HC_PRIORITY_DEFAULT);
	// g_ReGameHookchains->CBasePlayer_PostThink()->registerHook(&CBasePlayer_PostThink, HC_PRIORITY_DEFAULT);
	// // g_ReGameHookchains->CBasePlayer_RoundRespawn()->registerHook(&CBasePlayer_RoundRespawn, HC_PRIORITY_DEFAULT);

	return true;
}

CGameRules *InstallGameRules(IReGameHook_InstallGameRules *chain)
{
	return g_pGameRules = chain->callNext();
}

void HandleNetCommand(IRehldsHook_HandleNetCommand *chain, IGameClient *client, int8 a)
{
	chain->callOriginal(client, a);
}

void SV_SendServerinfo(IRehldsHook_SV_SendServerinfo *chain, sizebuf_t *buf, IGameClient *client)
{
	SEM_PRINT("%s %s %s", buf->buffername, buf->data, client->GetName());
	chain->callOriginal(buf, client);
}

bool InternalCommand(IReGameHook_InternalCommand *chain, edict_t *pEdict, const char *msg)
{
	SEM_PRINT("%d %s", pEdict->serialnumber, msg);
	return chain->callNext(pEdict, msg);
}