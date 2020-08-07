#include "Utility.h"
#include "Messages.h"

char* STRING_TO_CHAR(string str) { return (char*)STRING(ALLOC_STRING(str.c_str())); }

int IsEntValid(int index)
{
	return IsEntValid(INDEXENT(index));
}

int IsEntValid(edict_t* pEntity)
{
	if (FNullEnt(pEntity))
		return 0;

	if (pEntity->pvPrivateData)
		return 2;

	return 1;
}

edict_s* UTIL_GetAimingEntity(int index, float triggerDistance)
{
	auto pEntity = INDEXENT(index);

	Vector vSrc = pEntity->v.origin + pEntity->v.view_ofs;

	MAKE_VECTORS(pEntity->v.v_angle);
	Vector vDest = gpGlobals->v_forward * 10000.f + vSrc;

	TraceResult hTrace;
	TRACE_LINE(vSrc, vDest, dont_ignore_monsters, pEntity, &hTrace);

	vDest = hTrace.vecEndPos - vSrc;

	if (vDest.Length() > triggerDistance)
		return NULL;

	return hTrace.pHit;
}

p_GameObjectWeak_t UTIL_GetAimingObject(int index, float triggerDistance)
{
	auto pEntity = UTIL_GetAimingEntity(index, triggerDistance);

	if (FNullEnt(pEntity))
		return p_GameObjectWeak_t();

	auto entIndex = ENTINDEX(pEntity);

	if (ObjectManager::Instance().Has(entIndex))
		return ObjectManager::Instance().GetPtr(entIndex);
	else if (pEntity->v.iuser4 != 0)
	{
		if (ObjectManager::Instance().Has(pEntity->v.iuser4))
			return ObjectManager::Instance().GetPtr(pEntity->v.iuser4);
	}

	return p_GameObjectWeak_t();
}

Vector UTIL_GetEndPoint(int index, float triggerDistance)
{
	auto pEntity = INDEXENT(index);

	Vector vSrc = pEntity->v.origin + pEntity->v.view_ofs;

	MAKE_VECTORS(pEntity->v.v_angle);
	Vector vDest = gpGlobals->v_forward * 10000.f + vSrc;

	TraceResult hTrace;
	TRACE_LINE(vSrc, vDest, dont_ignore_monsters, pEntity, &hTrace);

	vDest = hTrace.vecEndPos - vSrc;

	float multiplier = 1.0f;
	float vecLen = vDest.Length();

	if (vecLen > triggerDistance)
		multiplier = triggerDistance / vecLen;

	return Vector(
		roundf(vSrc.x + vDest.x * multiplier),
		roundf(vSrc.y + vDest.y * multiplier),
		roundf(vSrc.z + vDest.z * multiplier)
	);
}

void UTIL_ClientPrint(edict_t* pEntity, MessageDest msg_dest, char* msg)
{
	if (!g_MsgTextMsg)
		return;				// :TODO: Maybe output a warning log?

	char c = msg[190];
	msg[190] = 0;			// truncate without checking with strlen()

	if (pEntity)
		MESSAGE_BEGIN(MSG_ONE, g_MsgTextMsg, NULL, pEntity);
	else
		MESSAGE_BEGIN(MSG_BROADCAST, g_MsgTextMsg);

	WRITE_BYTE(msg_dest);
	WRITE_STRING(STRING(ALLOC_STRING(msg)));
	MESSAGE_END();
	msg[190] = c;
}