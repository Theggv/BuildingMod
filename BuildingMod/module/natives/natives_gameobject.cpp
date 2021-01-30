#include "natives_gameobject.h"

#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/BuildObjects/FoundationSquare/FoundationSquare.h>
#include <game/BuildSystem/BuildObjects/FoundationTriangle/FoundationTriangle.h>

#include <game/BuildSystem/ObjectManager.h>

#include <game/Utility/EdictFlags.h>

HLTypeConversion typeConversion;

cell AMX_NATIVE_CALL Building_CreateObject(AMX* amx, cell* params)
{
	enum args_e { arg_count, arg_idcaller, arg_object_type};

	enum class objectType_e
	{
		OBJECT_FOUNDATION,
		OBJECT_FOUNDATIONTRIANGLE,
	};

	// int len;
	// sample
	// MF_GetAmxString(amx, params[arg_string], )
	// auto str = g_amxxapi.GetAmxString(amx, params[arg_idcaller], 0, &len);

	auto id = params[arg_idcaller];
	auto objectType = params[arg_object_type];

	edict_t* player = typeConversion.id_to_edict(id);
	GameObject* object = nullptr;

	switch ((objectType_e)objectType)
	{
	case objectType_e::OBJECT_FOUNDATION:
		object = new FoundationSquare(player);
		break;
	case objectType_e::OBJECT_FOUNDATIONTRIANGLE:
		object = new FoundationTriangle(player);
		break;
	default:
		break;
	}

	if (object != nullptr)
	{
		ObjectManager::Instance().Add(object);
		EdictFlags::SetPlayerSelectedObject(player, object->Id);
		object->Update();
	}

	return 0;
}

cell AMX_NATIVE_CALL Building_TryMakeSolid(AMX* amx, cell* params)
{
	enum args_e { arg_count, arg_idcaller };

	edict_t* player = typeConversion.id_to_edict(params[arg_idcaller]);

	auto objectId = EdictFlags::GetPlayerSelectedObject(player);

	auto objectPtr = ObjectManager::Instance().GetPtr(objectId).lock();

	bool isSuccess = false;

	if (objectPtr != nullptr)
		isSuccess = (*objectPtr)->TrySetState(BuildState::STATE_SOLID);

	objectPtr.reset();

	return isSuccess;
}

AMX_NATIVE_INFO GameObject_Natives[] =
{
	{"building_createobject",	Building_CreateObject },
	{"building_trymakesolid", Building_TryMakeSolid },

	{nullptr,			nullptr}
};

void RegisterNatives_GameObject()
{
	typeConversion.init();
	g_amxxapi.AddNatives(GameObject_Natives);
}
