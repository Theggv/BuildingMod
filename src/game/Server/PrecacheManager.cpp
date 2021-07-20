#include "PrecacheManager.h"
#include <boost/algorithm/string.hpp>
#include <game/Utility/Utility.h>

PrecacheManager::PrecacheManager()
{
	m_IsInit = false;

	char temp[FILENAME_MAX];
	g_amxxapi.BuildPathnameR(temp, sizeof(temp), "%s/BuildingMod/config.ini", LOCALINFO("amxx_datadir"));

	m_ConfigPath = temp;

	m_FoundationSquareModel = "";
	m_FoundationTriangleModel = "";
}

PrecacheManager &PrecacheManager::Instance()
{
	static PrecacheManager manager;

	return manager;
}

bool PrecacheManager::IsInit()
{
	return m_IsInit;
}

void PrecacheManager::PrecacheResources()
{
	if (!LoadConfig(m_ConfigPath))
	{
		SEM_PRINT("[Building Mod] Can't load config file.");
		return;
	}

	PRECACHE_MODEL((char *)STRING(UTIL_AllocString(m_FoundationSquareModel)));
	PRECACHE_MODEL((char *)STRING(UTIL_AllocString(m_FoundationTriangleModel)));
	PRECACHE_MODEL((char *)STRING(UTIL_AllocString(m_WallModel)));
	PRECACHE_MODEL((char *)STRING(UTIL_AllocString(m_DoorFrameModel)));

	m_LaserBeamId = PRECACHE_MODEL((char *)STRING(UTIL_AllocString("sprites/laserbeam.spr")));

	m_IsInit = true;

	SEM_PRINT("[Building Mod] Resources precached.");
}

string PrecacheManager::GetFoundationSquareModel()
{
	return m_FoundationSquareModel;
}

string PrecacheManager::GetFoundationTriangleModel()
{
	return m_FoundationTriangleModel;
}

string PrecacheManager::GetWallModel()
{
	return m_WallModel;
}

string PrecacheManager::GetDoorFrameModel()
{
	return m_DoorFrameModel;
}

int PrecacheManager::GetLaserBeamId()
{
	return m_LaserBeamId;
}

bool PrecacheManager::Parse_Settings(string str, string value)
{
	if (!_stricmp(str.c_str(), "FOUNDATION_MODEL"))
		m_FoundationSquareModel = value;
	else if (!_stricmp(str.c_str(), "FOUNDATION_TRIANGLE_MODEL"))
		m_FoundationTriangleModel = value;
	else if (!_stricmp(str.c_str(), "WALL_MODEL"))
		m_WallModel = value;
	else if (!_stricmp(str.c_str(), "DOOR_FRAME_MODEL"))
		m_DoorFrameModel = value;
	else
		return false;

	return true;
}

bool PrecacheManager::LoadConfig(string path)
{
	FILE *fp = fopen(path.c_str(), "rt");

	if (!fp)
		return false;

	char str[256];

	vector<string> parsed(2);
	string key, value;

	while (!feof(fp))
	{
		if (!fgets(str, sizeof(str) - 1, fp))
			break;

		boost::algorithm::split(parsed, str, boost::is_any_of("="));

		if (parsed.size() != 2)
			continue;

		key = parsed[0];
		value = parsed[1];

		boost::algorithm::trim(key);
		boost::algorithm::trim(value);
		boost::algorithm::erase_all(value, "\"");

		Parse_Settings(key, value);
	}

	return true;
}

static inline int IsCharSpecial(char j)
{
	return (j == ' ' || j == '"' || j == ';' || j == '\t' || j == '\r' || j == '\n');
}

void PrecacheManager::TrimSpace(char *pneedle)
{
	char *phaystack = pneedle;
	char *pbuf = pneedle;

	while (IsCharSpecial(*pbuf))
	{
		++pbuf;
	}

	while (*pbuf)
	{
		*phaystack++ = *pbuf++;
	}

	*phaystack = '\0';

	while (phaystack > pneedle && *--phaystack && IsCharSpecial(*phaystack))
	{
		*phaystack = '\0';
	}
}
