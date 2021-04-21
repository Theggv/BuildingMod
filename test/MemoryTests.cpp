#define BOOST_TEST_MODULE MemoryTests

#include <pch.h>
#include <boost/test/included/unit_test.hpp>

#include <game/BuildSystem/Components/IComponent.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>
#include <game/BuildSystem/Components/IColliderComponent.h>
#include <game/BuildSystem/Components/OwnerComponent.h>
#include <game/BuildSystem/Components/RendererComponent.h>
#include <game/BuildSystem/Components/VisualizerComponent.h>

#include <game/BuildSystem/Components/StabilityComponent/IObjectResolver.h>
#include <game/BuildSystem/Components/StabilityComponent/IConnectionPoints.h>

#include <Utility/Transform.h>
#include <game/BuildSystem/GameObject.h>
#include <game/BuildSystem/BuildingObjects/Objects.h>

class StabilityComponentMock : public IStabilityComponent
{
public:
	virtual void CalculateStability() override {}
};

class ObjectResolverMock : public IObjectResolver
{
public:
	virtual bool CanResolve(GameObject *object, GameObject *bindable) override
	{
		return false;
	}

protected:
	virtual void GenerateZones() override {}
};

class ConnectionPointsMock : public IConnectionPoints
{
public:
	virtual AimTestResult GetConnectionPoint(GameObject *object, GameObject *bindable, int zoneId) override
	{
		return AimTestResult(false);
	}

	virtual int GetZoneIdByPosition(GameObject *object, GameObject *bindable, vec3 pos) override
	{
		return 0;
	}

	virtual ConnectionTypes GetTypeByZone(int zoneId) override
	{
		return ConnectionTypes::Unknown;
	}
};

class GameObjectMock : public GameObject
{
public:
	void Connect(GameObject *other) override {}
};

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

BOOST_AUTO_TEST_CASE(TransformMemoryTest)
{
	auto transform = new Transform();
	delete transform;
}

BOOST_AUTO_TEST_CASE(GameObjectMemoryTest)
{
	auto object = new GameObjectMock();
	delete object;
}

BOOST_AUTO_TEST_CASE(FoundationSquareMemoryTest)
{
	auto object = new FoundationSquare(nullptr);
	delete object;
}

BOOST_AUTO_TEST_CASE(FoundationTriangleMemoryTest)
{
	auto object = new FoundationTriangle(nullptr);
	delete object;
}