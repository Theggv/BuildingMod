#ifndef _BUILDOBJECTS_FOUNDATION_FOUNDATION_
#define _BUILDOBJECTS_FOUNDATION_FOUNDATION_

#include <pch.h>
#include "game/BuildSystem/BuildObjects/GameObject.h"

class Foundation : public GameObject
{
public:
	Foundation(edict_t* owner);

	virtual void Start() override;
	virtual void Update() override;
protected:
	const int m_MinHeight = 16;
	const int m_MaxHeight = 72;
	
	virtual void AimPointHandler();
	virtual bool TraceGroundTest(Vector& viewPoint, Vector& viewAngle);
};

#endif // !_BUILDOBJECTS_FOUNDATION_FOUNDATION_
