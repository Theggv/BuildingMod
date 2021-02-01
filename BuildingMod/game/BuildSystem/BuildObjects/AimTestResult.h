#ifndef _BUILDOBJECTS_AIMTESTRESULT_
#define _BUILDOBJECTS_AIMTESTRESULT_

#include <pch.h>
#include <game/Geometry.h>

struct AimTestResult
{
public:
    AimTestResult(bool isPassed);
    AimTestResult(bool isPassed, vec3 origin);
    AimTestResult(bool isPassed, vec3 origin, double angle);

    bool m_IsPassed;
    vec3 m_Origin;
    double m_Angle;
};

#endif // !_BUILDOBJECTS_AIMTESTRESULT_
