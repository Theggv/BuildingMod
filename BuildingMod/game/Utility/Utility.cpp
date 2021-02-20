#include "Utility.h"
#include "Messages.h"

map<string, string_t> m_AllocatedStrings = map<string, string_t>();

int IsEntValid(int index)
{
	return IsEntValid(INDEXENT(index));
}

int IsEntValid(edict_t *pEntity)
{
	if (FNullEnt(pEntity))
		return 0;

	if (pEntity->pvPrivateData)
		return 2;

	return 1;
}

edict_t *UTIL_GetAimingEntity(int index, float triggerDistance)
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

	if (ObjectManager::Instance().HasEdict(pEntity))
		return ObjectManager::Instance().GetPtrByEdict(pEntity);

	// legacy probably, idk
	//
	// else if (pEntity->v.iuser4 != 0)
	// {
	// 	if (ObjectManager::Instance().Has(pEntity->v.iuser4))
	// 		return ObjectManager::Instance().GetPtr(pEntity->v.iuser4);
	// }

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
		roundf(vSrc.z + vDest.z * multiplier));
}

edict_t *UTIL_CreateEdict(string className)
{
	auto pEntity = CREATE_NAMED_ENTITY(UTIL_AllocString(className));

	if (!IsEntValid(pEntity))
	{
		SEM_PRINT("[GameObject] Can't create entity.");
		return nullptr;
	}

	// Set classname
	pEntity->v.classname = UTIL_AllocString(className);

	// Set size
	SET_SIZE(pEntity, Vector(-4, -4, 0), Vector(4, 4, 8));
	pEntity->v.solid = SOLID_BBOX;

	pEntity->v.nextthink = gpGlobals->time + 0.1f;

	return pEntity;
}

string_t UTIL_AllocString(string str)
{
	return ALLOC_STRING(str.c_str());
	auto it = m_AllocatedStrings.find(str);

	if (it != m_AllocatedStrings.end())
		return (*it).second;

	auto alloc = ALLOC_STRING(str.c_str());

	m_AllocatedStrings.insert(pair<string, string_t>(str, alloc));

	return alloc;
}

void UTIL_ClearAllocStrings()
{
	m_AllocatedStrings.clear();
}

void UTIL_ClientPrint(edict_t *pEntity, MessageDest msg_dest, char *msg)
{
	if (!g_MsgTextMsg)
		return; // :TODO: Maybe output a warning log?

	char c = msg[190];
	msg[190] = 0; // truncate without checking with strlen()

	if (pEntity)
		MESSAGE_BEGIN(MSG_ONE, g_MsgTextMsg, NULL, pEntity);
	else
		MESSAGE_BEGIN(MSG_BROADCAST, g_MsgTextMsg);

	WRITE_BYTE(msg_dest);
	WRITE_STRING(STRING(ALLOC_STRING(msg)));
	MESSAGE_END();
	msg[190] = c;
}

Vector UTIL_Rotate(Vector vec, float angle)
{
	float angle_sin = sin(angle * M_PI / 180);
	float angle_cos = cos(angle * M_PI / 180);

	return Vector(
		vec.x * angle_cos + vec.y * angle_sin,
		-vec.x * angle_sin + vec.y * angle_cos,
		vec.z);
}
