#include "Foundation.h"

Foundation::Foundation(edict_t* owner)
{
	AddComponent(new OwnerComponent(owner));
	AddComponent(new RendererComponent);
}

Foundation::~Foundation()
{
}