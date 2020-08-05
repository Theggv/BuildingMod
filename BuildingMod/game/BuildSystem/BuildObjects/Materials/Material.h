#ifndef _BUILDOBJECTS_MATERIALS_MATERIAL_
#define _BUILDOBJECTS_MATERIALS_MATERIAL_

#include <pch.h>

using namespace std;

class Material
{
public:
	float GetHpMultiplier();
private:
	float m_HpMultiplier;
};

#endif // !_BUILDOBJECTS_MATERIALS_MATERIAL_
