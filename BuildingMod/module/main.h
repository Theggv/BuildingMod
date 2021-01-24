#ifndef _MODULE_MAIN_
#define _MODULE_MAIN_

void OnAmxxAttach();
void OnAmxxDetach();

bool OnMetaAttach();
void OnMetaDetach();

void ServerDeactivate_Post();

int	pfnSpawn(edict_t* pent);

void SEM_PRINT(const char* fmt, ...);

#endif // !_MODULE_MAIN_
