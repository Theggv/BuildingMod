#include "natives_gameobject.h"

#include <game/BuildSystem/GameObject.h>

#include <game/BuildSystem/ObjectManager.h>
#include <game/BuildSystem/GameObjectFactory.h>

#include <game/Utility/EdictFlags.h>
#include <game/Utility/Utility.h>

HLTypeConversion typeConversion;

cell AMX_NATIVE_CALL Building_CreateObject(AMX *amx, cell *params)
{
	enum args_e
	{
		arg_count,
		arg_idcaller,
		arg_object_type
	};

	enum class objectType_e
	{
		OBJECT_FOUNDATION,
		OBJECT_FOUNDATIONTRIANGLE,
		OBJECT_WALL,
		OBJECT_DOORFRAME,
	};

	// int len;
	// sample
	// MF_GetAmxString(amx, params[arg_string], )
	// auto str = g_amxxapi.GetAmxString(amx, params[arg_idcaller], 0, &len);

	auto id = params[arg_idcaller];
	auto objectType = params[arg_object_type];

	edict_t *player = typeConversion.id_to_edict(id);

	// Check for existing object
	auto objectId = EdictFlags::GetPlayerSelectedObject(player);

	auto objectPtr = ObjectManager::Instance().GetPtr(objectId).lock();

	if (objectPtr != nullptr)
		return 0;

	p_GameObject_t object;
	GameObjectFactory *factory = new GameObjectFactory;

	switch ((objectType_e)objectType)
	{
	case objectType_e::OBJECT_FOUNDATION:
		object = factory->CreateFoundationSquare(player);
		break;
	case objectType_e::OBJECT_FOUNDATIONTRIANGLE:
		object = factory->CreateFoundationTriangle(player);
		break;
	case objectType_e::OBJECT_WALL:
		object = factory->CreateWall(player);
		break;
	case objectType_e::OBJECT_DOORFRAME:
		object = factory->CreateDoorFrame(player);
		break;
	default:
		break;
	}

	delete factory;

	if (object != nullptr)
	{
		EdictFlags::SetPlayerSelectedObject(player, object->Id);
		object->OnStart();
		object->OnUpdate();
	}

	return 0;
}

cell AMX_NATIVE_CALL Building_DeleteObject(AMX *amx, cell *params)
{
	enum args_e
	{
		arg_count,
		arg_idcaller,
		arg_object_id
	};

	auto id = params[arg_idcaller];
	auto objectId = params[arg_object_id];

	edict_t *player = typeConversion.id_to_edict(id);
	auto ptr = ObjectManager::Instance().GetPtr(objectId);

	if (ptr.expired())
		return 0;

	ObjectManager::Instance().Remove(ptr.lock());

	return 0;
}

cell AMX_NATIVE_CALL Building_TryMakeSolid(AMX *amx, cell *params)
{
	enum args_e
	{
		arg_count,
		arg_idcaller
	};

	edict_t *player = typeConversion.id_to_edict(params[arg_idcaller]);

	auto objectId = EdictFlags::GetPlayerSelectedObject(player);

	auto objectPtr = ObjectManager::Instance().GetPtr(objectId).lock();

	bool isSuccess = false;

	if (objectPtr != nullptr)
		isSuccess = objectPtr->TrySetState(BuildState::STATE_SOLID);

	objectPtr.reset();

	return isSuccess;
}

cell AMX_NATIVE_CALL Building_GetAimObject(AMX *amx, cell *params)
{
	enum args_e
	{
		arg_count,
		arg_idcaller
	};

	edict_t *player = typeConversion.id_to_edict(params[arg_idcaller]);

	auto object = UTIL_GetAimingObject(ENTINDEX(player));

	if (object.expired())
		return -1;

	return object.lock()->Id;
}

AMX_NATIVE_INFO GameObject_Natives[] =
	{
		{"building_createobject", Building_CreateObject},
		{"building_deleteobject", Building_DeleteObject},
		{"building_trymakesolid", Building_TryMakeSolid},
		{"building_getaimobject", Building_GetAimObject},

		{nullptr, nullptr},
};

void RegisterNatives_GameObject()
{
	typeConversion.init();
	g_amxxapi.AddNatives(GameObject_Natives);
}
