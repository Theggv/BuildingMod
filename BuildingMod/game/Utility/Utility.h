#ifndef _UTILITY_UTILITY_
#define _UTILITY_UTILITY_

#include <pch.h>
#include <game/BuildSystem/ObjectManager.h>

using namespace std;

extern map<string, string_t> m_AllocatedStrings;

int IsEntValid(int index);
int IsEntValid(edict_t* pEntity);

enum MessageDest
{
	PrintNofity = 1,
	PrintConsole = 2,
	PrintChat = 3,
	PrintCenter = 4
};

edict_t* UTIL_GetAimingEntity(int index, float triggerDistance = 10000.0f);
p_GameObjectWeak_t UTIL_GetAimingObject(int index, float triggerDistance = 10000.0f);
Vector UTIL_GetEndPoint(int index, float triggerDistance = 10000.0f);

edict_t* UTIL_CreateEdict(string className);

// idk is it better than default ALLOC_STRING
string_t UTIL_AllocString(string str);
void UTIL_ClearAllocStrings();

void UTIL_ClientPrint(edict_t* pEntity, MessageDest msg_dest, char* msg);

#endif // !_UTILITY_UTILITY_
