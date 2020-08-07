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
}

native building_ping();

/*
*	Spawn object with selected type
*/
native building_createobject(id, GameObjectType:type);

/*
*	Trying to make selected game object solid
*	@params:
*		@id - id of the player
*/
native building_trymakesolid(id);