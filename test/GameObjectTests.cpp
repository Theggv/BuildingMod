#define BOOST_TEST_MODULE GameObject

#include <pch.h>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(GameObjectDestructTest)
{
	auto object = new GameObject;
	delete object;
}

BOOST_AUTO_TEST_CASE(GameObjectIdGeneratorTest)
{
	auto vec = vector<GameObject*>();

	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(new GameObject);

		if (i > 0)
		{
			BOOST_CHECK_EQUAL(vec[i]->Id, vec[i - 1]->Id + 1);
		}
	}

	vec.clear();
}

unsigned int CalculuationTestHelper(GameObject* object, float x, float y)
{
	object->GetTransform()->GetPosition()->x(x);
	object->GetTransform()->GetPosition()->y(y);

	return object->GetWorldPositionFlags();
}

BOOST_AUTO_TEST_CASE(WorldPositionCalculationTest)
{
	auto object = new GameObject;

	BOOST_CHECK_EQUAL(CalculuationTestHelper(object, -3230.1f, -2289.3f), 9168);
	BOOST_CHECK_EQUAL(CalculuationTestHelper(object, 4095.0f, 4095.0f), 16383);
	BOOST_CHECK_EQUAL(CalculuationTestHelper(object, -4095.0f, -4095.0f), 0);

	delete object;
}
