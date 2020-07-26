#pragma once

void OnAmxxAttach();
bool OnMetaAttach();
void OnMetaDetach();

void ServerDeactivate_Post();

int	pfnSpawn(edict_t* pent);

void SEM_PRINT(const char* fmt, ...);