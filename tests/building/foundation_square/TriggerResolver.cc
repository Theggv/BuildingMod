
#include <gtest/gtest.h>
#include <building/foundation_square/TriggerResolver.h>
#include <building/foundation_square/trigger_zones/Foundation.h>
#include <building/constants.h>

#define EXPECT_NEAR_WITH_EPS(v1,v2) EXPECT_NEAR(v1,v2, 1e-6)

typedef FoundationSquareConnectionPoints ConnPoint;

using namespace FoundationSquareNamespace;

class FoundationResolverTests :public ::testing::Test
{
protected:
	void SetUp() override {
		// Foundation square resolver
		resolver = std::make_unique<TriggerResolver>();

		// Handlers of main resolver
		std::vector<std::unique_ptr<ITriggerZones>> handlers;
		handlers.push_back(std::make_unique<TriggerZonesFoundation>());

		for (auto& handler : handlers)
			resolver->AddResolver(std::move(handler));

		// Foundations
		foundation = std::make_unique<FoundationSquare>();
		other = std::make_unique<FoundationSquare>();
	}

	void IsVectorsEqual(vec3 expected, vec3 actual)
	{
		EXPECT_NEAR_WITH_EPS(expected.x, actual.x);
		EXPECT_NEAR_WITH_EPS(expected.y, actual.y);
		EXPECT_NEAR_WITH_EPS(expected.z, actual.z);
	}

	std::unique_ptr<TriggerResolver> resolver;
	std::unique_ptr<FoundationSquare> foundation;
	std::unique_ptr<FoundationSquare> other;
};

TEST_F(FoundationResolverTests, FoundationUpPointTest)
{
	auto ray = Ray(vec3(0, 250, 0), vec3(0, -1, 0));
	auto result = resolver->Resolve(foundation.get(), other.get(), ray);

	EXPECT_EQ(true, result.m_IsResolved);
	IsVectorsEqual(vec3(0, UNIT_SIZE, 0), result.m_Origin);
}

TEST_F(FoundationResolverTests, FoundationDownPointTest)
{
	auto ray = Ray(vec3(0, -250, 0), vec3(0, 1, 0));
	auto result = resolver->Resolve(foundation.get(), other.get(), ray);

	EXPECT_EQ(true, result.m_IsResolved);
	IsVectorsEqual(vec3(0, -UNIT_SIZE, 0), result.m_Origin);
}


TEST_F(FoundationResolverTests, FoundationLeftPointTest)
{
	auto ray = Ray(vec3(-250, 0, 0), vec3(1, 0, 0));
	auto result = resolver->Resolve(foundation.get(), other.get(), ray);

	EXPECT_EQ(true, result.m_IsResolved);
	IsVectorsEqual(vec3(-UNIT_SIZE, 0, 0), result.m_Origin);
}

TEST_F(FoundationResolverTests, FoundationRightPointTest)
{
	auto ray = Ray(vec3(250, 0, 0), vec3(-1, 0, 0));
	auto result = resolver->Resolve(foundation.get(), other.get(), ray);

	EXPECT_EQ(true, result.m_IsResolved);
	IsVectorsEqual(vec3(UNIT_SIZE, 0, 0), result.m_Origin);
}

TEST_F(FoundationResolverTests, FoundationWithRotationTest)
{
	foundation->GetTransform()->GetRotation()->y(90);

	auto ray = Ray(vec3(250, 0, 0), vec3(-1, 0, 0));
	auto result = resolver->Resolve(foundation.get(), other.get(), ray);

	EXPECT_EQ(true, result.m_IsResolved);
	IsVectorsEqual(vec3(UNIT_SIZE, 0, 0), result.m_Origin);
	EXPECT_NEAR_WITH_EPS(-90, result.m_Angle);
}