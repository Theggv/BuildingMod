#ifndef _UTILITY_MESSAGES_
#define _UTILITY_MESSAGES_

#include <pch.h>

extern int g_MsgTextMsg;

typedef struct UserMsg_s
{
	const char* name;
	int* id;
} UserMsg_t;

extern UserMsg_s g_UserMsg[];

int pfnRegUserMsg_Post(const char* pszName, int iSize);

#endif // !_UTILITY_MESSAGES_
