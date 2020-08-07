#include "Messages.h"

int g_MsgTextMsg;

UserMsg_s g_UserMsg[]
{
	{"TextMsg", &g_MsgTextMsg }
};

int pfnRegUserMsg_Post(const char* pszName, int iSize)
{
	for (auto msg : g_UserMsg)
	{
		if (!strcmp(msg.name, pszName))
		{
			*msg.id = META_RESULT_ORIG_RET(int);
		}
	}

	RETURN_META_VALUE(MRES_IGNORED, 0);
}