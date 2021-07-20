#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <game/BuildSystem/GameObject.h>
#include "mocks.h"

class GameObjectMock : public GameObject
{
public:
	inline void Connect(p_GameObject_t other) override {}
};

BOOST_AUTO_TEST_SUITE(GameObjectSuite)

BOOST_AUTO_TEST_CASE(GameObjectDestructTest)
{
	auto object = InitObject(new GameObjectMock);

	ObjectManager::Instance().Clear();
}

BOOST_AUTO_TEST_CASE(GameObjectIdGeneratorTest)
{
	vector<p_GameObject_t> vec;

	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(InitObject(new GameObjectMock));

		if (i > 0)
		{
			BOOST_CHECK_EQUAL(vec[i]->Id, vec[i - 1]->Id + 1);
		}
	}

	vec.clear();
	ObjectManager::Instance().Clear();
}

unsigned int CalculuationTestHelper(GameObject *object, float x, float y)
{
	object->GetTransform()->GetPosition()->x(x);
	object->GetTransform()->GetPosition()->y(y);

	return object->GetWorldPositionFlags();
}
BOOST_AUTO_TEST_SUITE_END()