#ifndef _BUILDOBJECTS_COMPONENTS_RENDERERCOMPONENT_
#define _BUILDOBJECTS_COMPONENTS_RENDERERCOMPONENT_

#include <pch.h>
#include "IComponent.h"

class Material;

using namespace std;

class RendererComponent : public IComponent
{
public:
	Material* GetMaterial();

	string GetModel();
	void SetModel(string model);
private:
	string m_Model;
	Material* m_Material;
};

#endif // !_BUILDOBJECTS_COMPONENTS_RENDERERCOMPONENT_
