#include "Foundation.h"
#include <game/BuildSystem/BuildObjects/Components/OwnerComponent.h>
#include <game/BuildSystem/BuildObjects/Components/RendererComponent.h>

Foundation::Foundation(edict_t* owner)
{
	AddComponent(new OwnerComponent(owner));
	AddComponent(new RendererComponent);
}

Foundation::~Foundation()
{
}