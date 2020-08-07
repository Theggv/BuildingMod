#ifndef _BUILDOBJECTS_COMPONENTS_RENDERERCOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_RENDERERCOMPONENT_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/Materials/Material.h>

class RendererComponent : public IComponent
{
public:
	Material* GetMaterial();
private:
	string m_Model;
	Material* m_Material;
};

#endif // !_BUILDOBJECTS_COMPONENTS_RENDERERCOMPONENT_
