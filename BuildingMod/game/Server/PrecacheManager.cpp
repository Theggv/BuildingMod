#include "PrecacheManager.h"

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


	}

	return false;
}
