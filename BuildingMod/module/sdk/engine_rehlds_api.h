#ifndef _INCLUDE_REHLDS_API_H_
#define _INCLUDE_REHLDS_API_H_

#pragma once

typedef enum sv_delta_s {
	sv_packet_nodelta,
	sv_packet_delta
} sv_delta_t;

typedef struct packet_entities_s {
	int num_entities;
	unsigned char flags[32];
	entity_state_t* entities;
} packet_entities_t;

#include <rehlds_api.h>

extern IRehldsApi* g_RehldsApi;
extern IRehldsHookchains* g_RehldsHookchains;
extern bool RehldsApi_Init();

#endif //_INCLUDE_REHLDS_API_H_
