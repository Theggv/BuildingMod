#include "natives_ping.h"

cell AMX_NATIVE_CALL Building_Ping(AMX* amx, cell* params)
{
	SEM_PRINT("[Building Mod] Pong.");
	return 0;
}

AMX_NATIVE_INFO Ping_Natives[] =
{
	{"building_ping",	Building_Ping },

	{nullptr,			nullptr}
};

void RegisterNatives_Ping()
{
	g_amxxapi.AddNatives(Ping_Natives);
}
