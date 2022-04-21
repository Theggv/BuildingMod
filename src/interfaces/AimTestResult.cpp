#include "AimTestResult.h"

AimTestResult::AimTestResult(bool isPassed, vec3 origin, double angle)
{
    m_IsPassed = isPassed;
    m_Origin = origin;
    m_Angle = angle;

    while (m_Angle > 180)
        m_Angle -= 360;
}

AimTestResult::AimTestResult(bool isPassed, vec3 origin)
    : AimTestResult(isPassed, origin, 0)
{
}

AimTestResult::AimTestResult(bool isPassed)
    : AimTestResult(isPassed, vec3::Zero(), 0)
{
}