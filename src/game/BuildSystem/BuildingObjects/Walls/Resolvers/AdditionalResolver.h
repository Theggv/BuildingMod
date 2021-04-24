#ifndef _WALLS_RESOLVERS_ADDITIONALRESOLVER_
#define _WALLS_RESOLVERS_ADDITIONALRESOLVER_

#include <pch.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/ObjectManager.h>
#include <game/Geometry.h>

#include <game/BuildSystem/BuildingObjects/Objects.h>

using namespace std;

namespace WallBaseResolvers
{
	class AdditionalResolver : public IObjectResolver
	{

	public:
		AdditionalResolver();

		virtual AimTestResult TryConnect(
			ray ray,
			p_GameObject_t object,
			p_GameObject_t bindable) override;

		virtual void AddConnection(
			p_GameObject_t object,
			p_GameObject_t bindable) override;

		virtual bool CanResolve(
			p_GameObject_t object,
			p_GameObject_t bindable) override;

	protected:
		void GenerateZones() override;

	private:
		bool IsTouch(Shape, Shape);
	};
}

#endif // !_WALLS_RESOLVERS_ADDITIONALRESOLVER_
