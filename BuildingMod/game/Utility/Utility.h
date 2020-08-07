#ifndef _UTILITY_UTILITY_
#define _UTILITY_UTILITY_

#include <pch.h>
#include <game/BuildSystem/ObjectManager.h>

extern char* STRING_TO_CHAR(string str);

int IsEntValid(int index);
int IsEntValid(edict_t* pEntity);

enum MessageDest
{
	PrintNofity = 1,
	PrintConsole = 2,
	PrintChat = 3,
	PrintCenter = 4
};

edict_s* UTIL_GetAimingEntity(int index, float triggerDistance = 10000.0f);
p_GameObjectWeak_t UTIL_GetAimingObject(int index, float triggerDistance = 10000.0f);
Vector UTIL_GetEndPoint(int index, float triggerDistance = 10000.0f);

void UTIL_ClientPrint(edict_t* pEntity, MessageDest msg_dest, char* msg);

#endif // !_UTILITY_UTILITY_
