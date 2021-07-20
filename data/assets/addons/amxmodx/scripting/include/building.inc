#if defined _building_included
	#endinput
#endif

#define _building_included

#if AMXX_VERSION_NUM >= 175
	#pragma reqlib building
	#if !defined AMXMODX_NOAUTOLOAD
		#pragma loadlib building
	#endif
#else
	#pragma library building
#endif

enum GameObjectType
{
	OBJECT_FOUNDATION,
	OBJECT_FOUNDATIONTRIANGLE,
	OBJECT_WALL,
	OBJECT_DOORFRAME,
}

native building_ping();

/**
*	Spawn object with selected type
*
*	@noreturn
*/
native building_createobject(id, GameObjectType:type);


/**
*	Delete object with given objectId
*
*	@param id - player id
*	@param objectId - object id
*	@return bool - is success
*/
native building_deleteobject(id, objectId);

/**
*	Trying to make selected game object solid
*	@param id - player id
*	@return bool - is success
*/
native building_trymakesolid(id);

/**
*	Get object id by players aim
*	
*	@param id - player id
*	@return int - object id or -1 if not success
*/
native building_getaimobject(id);