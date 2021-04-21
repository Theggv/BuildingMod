#ifndef _UTILITY_EDICTFLAGS_
#define _UTILITY_EDICTFLAGS_

#include <pch.h>

class EdictFlags
{
public:
	static void SetFlags(edict_t* edict, unsigned int flags);
	static bool HasFlag(edict_t* edict, unsigned int flag);
	static unsigned int GetFlags(edict_t* edict);

	static void SetPlayerSelectedObject(edict_t* player, int objectId);
	static int GetPlayerSelectedObject(edict_t* player);
};

#endif // !_UTILITY_EDICTFLAGS_
