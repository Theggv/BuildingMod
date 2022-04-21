#ifndef _BUILDINGOBJECTS_COMPONENTS_RENDERERCOMPONENT_
#define _BUILDINGOBJECTS_COMPONENTS_RENDERERCOMPONENT_

#include <pch.h>
#include "IComponent.h"

class Material;

using namespace std;

class RendererComponent : public IComponent
{
public:
	RendererComponent(double fixAngle = 0.0);
	
	Material *GetMaterial();

	string GetModel();
	void SetModel(string model);
	double GetFixAngle();

private:
	string m_Model;
	Material *m_Material;
	double m_FixAngle;
};

#endif // !_BUILDINGOBJECTS_COMPONENTS_RENDERERCOMPONENT_
