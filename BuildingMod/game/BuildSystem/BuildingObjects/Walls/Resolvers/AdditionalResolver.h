#ifndef _WALLS_RESOLVERS_ADDITIONALRESOLVER_
#define _WALLS_RESOLVERS_ADDITIONALRESOLVER_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace std;

namespace WallsResolvers
{
	class AdditionalResolver : public IObjectResolver
	{
	public:
		AdditionalResolver();

		virtual AimTestResult TryConnect(ray ray, GameObject *object, GameObject *bindable) override;

		virtual void AddConnection(GameObject *object, GameObject *bindable) override;

		virtual bool CanResolve(GameObject *object, GameObject *bindable) override;

	protected:
		void GenerateZones() override;
	};
}

#endif // !_WALLS_RESOLVERS_ADDITIONALRESOLVER_
