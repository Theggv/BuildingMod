#include <pch.h>

void OnAmxxAttach()
{
	SEM_PRINT("[Building Mod] Module loaded.");

	RegisterNatives_Ping();
}

bool OnMetaAttach()
{
	SEM_PRINT("[Building Mod] Attached to metamod");
	return true;
}

void OnMetaDetach()
{
	//ObjectManager::Instance().Clear();
}

void ServerDeactivate_Post()
{
	//ObjectManager::Instance().Clear();
}

int	pfnSpawn(edict_t* pent)
{
	/*auto mngr = PrecacheManager::Instance();

	if (mngr.IsInit())
		RETURN_META_VALUE(MRES_IGNORED, 0);

	mngr.SetInit();
	mngr.PrecacheResources();*/

	RETURN_META_VALUE(MRES_IGNORED, 0);
}

void SEM_PRINT(const char* fmt, ...)
{
	va_list ap;
	uint32 len;
	char buf[1048];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	len = strlen(buf);

	if (len < sizeof(buf) - 2) {
		strcat(buf, "\n");
	}
	else {
		buf[len - 1] = '\n';
	}

	SERVER_PRINT(buf);
}