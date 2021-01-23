#ifndef _BUILDOBJECTS_FOUNDATIONTRIANGLE_
#define _BUILDOBJECTS_FOUNDATIONTRIANGLE_

#include <pch.h>
#include <game/BuildSystem/BuildObjects/Foundation/Foundation.h>

class FoundationTriangle : public Foundation
{
public:
	FoundationTriangle(edict_t *owner);

	virtual void Start() override;
	virtual void Update() override;

protected:
	virtual void AimPointHandler() override;
	virtual bool TraceGroundTest(Vector &viewPoint, Vector &viewAngle) override;
};

#endif // !_BUILDOBJECTS_FOUNDATIONTRIANGLE_
