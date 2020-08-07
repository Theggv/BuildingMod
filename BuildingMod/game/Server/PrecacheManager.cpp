#include "PrecacheManager.h"

PrecacheManager::PrecacheManager()
{
	m_IsInit = false;

	m_ConfigPath = string(LOCALINFO("amxx_datadir")) + "/BuildingMod/config.ini";
	m_FoundationModel = "";
}

PrecacheManager& PrecacheManager::Instance()
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
	LoadConfig(m_ConfigPath);

	m_IsInit = true;
}

string PrecacheManager::GetFoundationModel()
{
	return m_FoundationModel;
}

bool PrecacheManager::Parse_Settings(const char* str, const char* value)
{
	if (!_stricmp(str, "FOUNDATION_MODEL"))
		m_FoundationModel = value;
	else
		return false;

	return true;
}

bool PrecacheManager::LoadConfig(string path)
{
	FILE* fp = fopen(path.c_str(), "rt");

	if (!fp)
		return false;

	char* value;
	char buf[256];

	while (!feof(fp))
	{
		if (!fgets(buf, sizeof(buf) - 1, fp))
			break;

		value = strchr(buf, '=');

		if (value == nullptr) {
			continue;
		}

		*(value++) = '\0';

		TrimSpace(buf);
		TrimSpace(value);

		if (*buf == '\0' || *value == '\0' || Parse_Settings(buf, value)) {
			continue;
		}
	}

	return false;
}

static inline int IsCharSpecial(char j)
{
	return (j == ' ' || j == '"' || j == ';' || j == '\t' || j == '\r' || j == '\n');
}

void PrecacheManager::TrimSpace(char* pneedle)
{
	char* phaystack = pneedle;
	char* pbuf = pneedle;

	while (IsCharSpecial(*pbuf)) {
		++pbuf;
	}

	while (*pbuf) {
		*phaystack++ = *pbuf++;
	}

	*phaystack = '\0';

	while (phaystack > pneedle && *--phaystack && IsCharSpecial(*phaystack)) {
		*phaystack = '\0';
	}
}
