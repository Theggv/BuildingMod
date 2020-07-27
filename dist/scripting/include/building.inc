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

native building_ping();