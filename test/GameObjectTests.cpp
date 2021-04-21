#define BOOST_TEST_MODULE GameObject

#include <pch.h>
#include <boost/test/included/unit_test.hpp>
#include <game/BuildSystem/GameObject.h>

class GameObjectMock : public GameObject
{
public:
	inline void Connect(GameObject *other) override {}
};

BOOST_AUTO_TEST_CASE(GameObjectDestructTest)
{
	auto object = new GameObjectMock;
	delete object;
}

BOOST_AUTO_TEST_CASE(GameObjectIdGeneratorTest)
{
	vector<GameObject *> vec;

	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(new GameObjectMock);

		if (i > 0)
		{
			BOOST_CHECK_EQUAL(vec[i]->Id, vec[i - 1]->Id + 1);
		}
	}

	for (auto obj : vec)
		delete obj;

	vec.clear();
	vector<GameObject *>().swap(vec);
}

unsigned int CalculuationTestHelper(GameObject *object, float x, float y)
{
	object->GetTransform()->GetPosition()->x(x);
	object->GetTransform()->GetPosition()->y(y);

	return object->GetWorldPositionFlags();
}