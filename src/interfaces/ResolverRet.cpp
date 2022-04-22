#include "ResolverRet.h"

ResolverRet::ResolverRet(bool isResolved, vec3 origin, double angle)
{
    m_IsResolved = isResolved;
    m_Origin = origin;
    m_Angle = angle;

    while (m_Angle > 180)
        m_Angle -= 360;
}

ResolverRet::ResolverRet(bool isResolved, vec3 origin)
    : ResolverRet(isResolved, origin, 0)
{
}

ResolverRet::ResolverRet(bool isResolved)
    : ResolverRet(isResolved, vec3::Zero(), 0)
{
}