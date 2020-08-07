#ifndef _BUILDOBJECTS_FOUNDATION_FOUNDATION_
#define _BUILDOBJECTS_FOUNDATION_FOUNDATION_

#include <pch.h>
#include "game/BuildSystem/BuildObjects/GameObject.h"

class Foundation : public GameObject
{
public:
	Foundation(edict_t* owner);
	~Foundation();

	static string FoundationModel;
private:
};

#endif // !_BUILDOBJECTS_FOUNDATION_FOUNDATION_
