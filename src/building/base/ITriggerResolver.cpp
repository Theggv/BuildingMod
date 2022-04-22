#include "ITriggerResolver.h"
#include <math/math_include.h>

ITriggerResolver::~ITriggerResolver()
{
}

void ITriggerResolver::AddResolver(std::unique_ptr<ITriggerZones> &resolver)
{
	m_resolvers.push_back(std::move(resolver));
}

ResolverRet ITriggerResolver::Resolve(BuildingObject* object, BuildingObject* other, Ray& ray)
{
	for (auto& resolver : m_resolvers)
	{
		if (resolver->CanResolve(object, other))
		{
			auto connectionPoint = resolver->GetConnectionPoint(object, ray);

			if (!connectionPoint.m_IsResolved)
				continue;

			auto offset = other->GetObjectOffset(connectionPoint.m_Angle);

			auto objectAngle = object->GetTransform()->GetRotation()->y();
			auto& objectPos = *object->GetTransform()->GetPosition();

			auto mat = mat4::RotationMatrix(objectAngle) *
				mat4::TranslateMatrix(objectPos);

			auto pos = (connectionPoint.m_Origin + offset.pos).Transform(mat);

			return ResolverRet(true, pos, connectionPoint.m_Angle + objectAngle);
		}
	}

	return ResolverRet(false);
}
