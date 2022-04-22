#ifndef _INTERFACES_RESOLVERRET_H_
#define _INTERFACES_RESOLVERRET_H_

#include <pch.h>
#include <math/math_include.h>

struct ResolverRet
{
public:
	ResolverRet(bool isResolved);
	ResolverRet(bool isResolved, vec3 origin);
	ResolverRet(bool isResolved, vec3 origin, double angle);

	bool m_IsResolved;
	vec3 m_Origin;
	double m_Angle;
};

#endif // !_INTERFACES_RESOLVERRET_H_
