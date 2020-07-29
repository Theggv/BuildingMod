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
