#include "EdictFlags.h"

void EdictFlags::SetFlags(edict_t* edict, unsigned int flags)
{
	edict->v.vuser4.x = flags;
}

bool EdictFlags::HasFlag(edict_t* edict, unsigned int flag)
{
	return (unsigned int)edict->v.vuser4.x & flag;
}

unsigned int EdictFlags::GetFlags(edict_t* edict)
{
	return (unsigned int)edict->v.vuser4.x;
}

void EdictFlags::SetPlayerSelectedObject(edict_t* player, int objectId)
{
	player->v.vuser3.x = objectId;
}

int EdictFlags::GetPlayerSelectedObject(edict_t* player)
{
	return player->v.vuser3.x;
}