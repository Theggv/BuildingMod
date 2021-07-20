#include "FoundationBase.h"

#include <game/BuildSystem/Components/RendererComponent.h>
#include <game/BuildSystem/Components/IColliderComponent.h>
#include <game/BuildSystem/Components/VisualizerComponent.h>
#include <game/BuildSystem/Components/IStabilityComponent.h>

#include <game/Utility/Utility.h>
#include <game/Server/PrecacheManager.h>
#include <game/BuildSystem/BuildingObjects/Objects.h>

const double FoundationBase::m_ModelSize = 112;
const double FoundationBase::m_MinHeight = 8;
const double FoundationBase::m_MaxHeight = m_ModelSize - m_MinHeight;

FoundationBase::FoundationBase(edict_t *owner) : BuildingObject(owner)
{
	auto visualizer = new VisualizerComponent(0.3);
	visualizer->Disable();

	AddComponent(visualizer);
}

void FoundationBase::OnStart()
{
	BuildingObject::OnStart();
}

void FoundationBase::OnUpdate()
{
	BuildingObject::OnUpdate();

	if (m_State != BuildState::STATE_SOLID)
	{
		AimHandler();
	}
}

void FoundationBase::OnStateUpdated()
{
	BuildingObject::OnStateUpdated();

	// OnUpdate Connections

	if (GetState() != BuildState::STATE_SOLID)
		return;

	auto objects = ObjectManager::Instance().GetObjectsInArea(
		*GetTransform()->GetPosition());

	for (auto object : objects)
	{
		if (object.expired())
			continue;

		auto gameObject = object.lock();

		if (gameObject->Id == this->Id)
			continue;

		if (dynamic_pointer_cast<FoundationBase>(gameObject) != nullptr ||
			dynamic_pointer_cast<WallBase>(gameObject) != nullptr)
		{
			Connect(gameObject);
		}
	}

	auto stability = GetComponent<IStabilityComponent>();
	if (stability)
		stability->StartCalculation();
}

void FoundationBase::AimHandler()
{
	auto ownerComponent = GetComponent<OwnerComponent>();

	auto viewPoint = ownerComponent->GetAimDest(250.0);
	viewPoint.z += m_MinHeight;

	auto aimRay = ownerComponent->GetAimRay(viewPoint, 500.0);
	auto angles = ownerComponent->GetViewAngles();

	auto aimTest = AimTest(aimRay);

	if (!aimTest.m_IsPassed)
	{
		aimTest.m_Origin = viewPoint;
		aimTest.m_Angle = angles.y;
	}

	auto interTest = IntersectionTest(aimTest);

	auto groundTest = TraceGroundTest(aimTest);

	if (interTest.m_IsPassed && groundTest.m_IsPassed)
	{
		if (aimTest.m_IsPassed)
		{
			auto maxHeightTest = MaxHeightTest(aimTest, groundTest);

			TrySetState(maxHeightTest.m_IsPassed
							? BuildState::STATE_CAN_BUILD
							: BuildState::STATE_CANNOT_BUILD);

			GetTransform()->GetPosition()->setVector(maxHeightTest.m_Origin);
			GetTransform()->GetRotation()->y(maxHeightTest.m_Angle);

			return;
		}
		else
		{
			TrySetState(BuildState::STATE_CAN_BUILD);

			GetTransform()->GetPosition()->setVector(groundTest.m_Origin);
			GetTransform()->GetRotation()->y(groundTest.m_Angle);

			return;
		}
	}

	TrySetState(BuildState::STATE_CANNOT_BUILD);

	GetTransform()->GetPosition()->setVector(viewPoint);
	GetTransform()->GetRotation()->y(angles.y);
}

AimTestResult FoundationBase::MaxHeightTest(AimTestResult aimTest, AimTestResult groundTest)
{
	auto isTooHigh = groundTest.m_Origin.z < aimTest.m_Origin.z;

	return AimTestResult(!isTooHigh, aimTest.m_Origin, aimTest.m_Angle);
}

AimTestResult FoundationBase::MinHeightTest(AimTestResult aimTest, AimTestResult groundTest)
{
	auto isTooLow = aimTest.m_Origin.z < groundTest.m_Origin.z;

	return AimTestResult(!isTooLow, aimTest.m_Origin);
}

AimTestResult FoundationBase::IntersectionTest(AimTestResult result)
{
	auto objects = ObjectManager::Instance().GetObjectsInArea(result.m_Origin);

	auto shape = GetShape(AimTestResult(
		result.m_IsPassed,
		result.m_Origin,
		result.m_Angle));

	for (auto object : objects)
	{
		if (object.expired())
			continue;

		auto foundation = dynamic_pointer_cast<FoundationBase>(object.lock());

		if (foundation == nullptr)
		{
			object.reset();
			continue;
		}

		if (foundation->Id == this->Id)
			continue;

		auto otherShape = foundation->GetShape();

		if (shape.IsIntersect(otherShape))
			return AimTestResult(false, result.m_Origin, result.m_Angle);
	}

	return AimTestResult(true, result.m_Origin, result.m_Angle);
}
