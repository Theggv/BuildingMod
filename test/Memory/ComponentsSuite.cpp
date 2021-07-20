#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <game/BuildSystem/Components/IComponent.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>
#include <game/BuildSystem/Components/IColliderComponent.h>
#include <game/BuildSystem/Components/OwnerComponent.h>
#include <game/BuildSystem/Components/RendererComponent.h>
#include <game/BuildSystem/Components/VisualizerComponent.h>

#include <game/BuildSystem/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/Components/StabilityComponent/IConnectionPoints.h>

class StabilityComponentMock : public IStabilityComponent
{
public:
	virtual void CalculatePrimaryStability() override {}
	virtual void CalculateSecondaryStability(int cycle = 0) override {}
};

class ObjectResolverMock : public IObjectResolver
{
public:
	virtual bool CanResolve(p_GameObject_t object, p_GameObject_t bindable) override
	{
		return false;
	}

protected:
	virtual void GenerateZones() override {}
};

class ConnectionPointsMock : public IConnectionPoints
{
public:
	virtual AimTestResult GetConnectionPoint(p_GameObject_t object, p_GameObject_t bindable, int zoneId) override
	{
		return AimTestResult(false);
	}

	virtual int GetZoneIdByPosition(p_GameObject_t object, p_GameObject_t bindable, vec3 pos) override
	{
		return 0;
	}

	virtual ConnectionTypes GetTypeByZone(int zoneId) override
	{
		return ConnectionTypes::Unknown;
	}
};

BOOST_AUTO_TEST_SUITE(ComponentsSuite)

BOOST_AUTO_TEST_CASE(IComponentMemoryTest)
{
	auto component = new IComponent;
	delete component;
}

BOOST_AUTO_TEST_CASE(IStabilityComponentMemoryTest)
{
	auto component = new StabilityComponentMock();
	delete component;
}

BOOST_AUTO_TEST_CASE(IColliderComponentMemoryTest)
{
	auto component = new IColliderComponent();
	delete component;
}

BOOST_AUTO_TEST_CASE(OwnerComponentMemoryTest)
{
	auto component = new OwnerComponent(nullptr);
	delete component;
}

BOOST_AUTO_TEST_CASE(RendererComponentMemoryTest)
{
	auto component = new RendererComponent();
	delete component;
}

BOOST_AUTO_TEST_CASE(VisualizerComponentMemoryTest)
{
	auto component = new VisualizerComponent();
	delete component;
}

BOOST_AUTO_TEST_CASE(IObjectResolverMemoryTest)
{
	auto component = new ObjectResolverMock();
	delete component;
}

BOOST_AUTO_TEST_CASE(IConnectionPointsMemoryTest)
{
	auto component = new ConnectionPointsMock();
	delete component;
}

BOOST_AUTO_TEST_SUITE_END()
