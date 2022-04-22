#if !defined(_FOUNDATION_SQUARE_TRIGGER_RESOLVER_H_)
#define _FOUNDATION_SQUARE_TRIGGER_RESOLVER_H_

#include <pch.h>
#include <building/base/ITriggerResolver.h>
#include "ConnectionPoints.h"


namespace FoundationSquareNamespace
{
	class TriggerResolver : public ITriggerResolver
	{
	public:
		TriggerResolver();
		~TriggerResolver();

		/// <summary>
		/// Checks if class can resolve that kind of object
		/// </summary>
		/// <param name="object">Object to attach</param>
		/// <returns></returns>
		bool CanResolve(BuildingObject* object) override;
	};
}

#endif // _FOUNDATION_SQUARE_TRIGGER_RESOLVER_H_
