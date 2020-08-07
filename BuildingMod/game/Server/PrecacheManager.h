#ifndef _SERVER_PRECACHEMANAGER_
#define _SERVER_PRECACHEMANAGER_

#include <pch.h>

using namespace std;

class PrecacheManager
{
public:
	static PrecacheManager& Instance();

	bool IsInit();
	void PrecacheResources();

	string GetFoundationModel();
private:
	PrecacheManager();

	bool LoadConfig(string path);
	void TrimSpace(char*);
	bool Parse_Settings(const char* str, const char* value);

	bool m_IsInit;
	string m_ConfigPath;

	// models region

	string m_FoundationModel;
};

#endif // !_SERVER_PRECACHEMANAGER_
