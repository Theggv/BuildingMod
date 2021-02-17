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

	string GetFoundationSquareModel();
	string GetFoundationTriangleModel();
	string GetWallModel();

	int GetLaserBeamId();
private:
	PrecacheManager();

	bool LoadConfig(string path);
	void TrimSpace(char*);
	bool Parse_Settings(string str, string value);

	bool m_IsInit;
	string m_ConfigPath;

	// models region

	string m_FoundationSquareModel;
	string m_FoundationTriangleModel;
	string m_WallModel;

	int m_LaserBeamId;
};

#endif // !_SERVER_PRECACHEMANAGER_
