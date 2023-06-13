#include "AvoidCollisionsSystem.h"

#include "TransformInfo.h"
#include "Implementation/SpawnFeature/UnitMarker.h"
#include "Implementation/ArcherGame.h"
#include "Implementation/CommonComponents/BoxInfo.h"

#include "raymath.h"


Vector3 InterpConstantTo(Vector3 const& Current, Vector3 const& Target, float DeltaTime, float InterpSpeed)
{
	const Vector3 Delta = Vector3Subtract(Target, Current);
	const float DeltaM = Vector3Length(Delta);
	const float MaxStep = InterpSpeed * DeltaTime;

	if (DeltaM > MaxStep)
	{
		if (MaxStep > 0.f)
		{
			const Vector3 DeltaN = { Delta.x / DeltaM,Delta.y / DeltaM,Delta.z / DeltaM };
			return Vector3Add(Current, { DeltaN.x * MaxStep, DeltaN.y * MaxStep, DeltaN.z * MaxStep });
		}
		return Current;
	}

	return Target;
}

BoundingBox BoxComponentToBB(Vector3 pos,BoxInfo const& box_component)
{
	const BoundingBox bb = { { pos.x - box_component.size.x / 2,
									 pos.y - box_component.size.y / 2,
									 pos.z - box_component.size.z / 2 },
		{
		pos.x + box_component.size.x / 2,
			pos.y + box_component.size.y / 2,
			pos.z + box_component.size.z / 2
	} };

	return bb;
}

void AvoidCollisionsSystem::execute(entt::registry& world)
{
	const auto view = world.view<TransformInfo, BoxInfo, UnitMarker>();

	for (auto& [entity, transform, box] : view.each())
	{
		for (auto& [entity2, transform2, box2] : view.each())
		{
			if(entity != entity2 && CheckCollisionBoxes(BoxComponentToBB(transform.transform.translation,box), BoxComponentToBB(transform2.transform.translation, box2)))
			{
				auto c1 = Vector3Add(BoxComponentToBB(transform.transform.translation, box).min, BoxComponentToBB(transform.transform.translation, box).max);
				c1 = { c1.x / 2.f,c1.y / 2.f, c1.z / 2.f };
				auto c2 = Vector3Add(BoxComponentToBB(transform2.transform.translation, box2).min, BoxComponentToBB(transform2.transform.translation, box2).max);
				c2 = { c2.x / 2.f,c2.y / 2.f, c2.z / 2.f };
				if (Vector3Equals(c1,c2))
				{
					auto cur = GetRandomValue(0, 360);
					auto opp = (cur + 180) % 360;
					transform.transform.translation = Vector3Add(transform.transform.translation, Vector3Scale(Vector3RotateByAxisAngle({ 1,0,0 }, { 0,1,0 }, static_cast<float>(cur)), 0.15f));
					transform2.transform.translation = Vector3Add(transform2.transform.translation, Vector3Scale(Vector3RotateByAxisAngle({ 1,0,0 }, { 0,1,0 }, static_cast<float>(opp)), 0.15f));
				}
				else
				{
					transform.transform.translation = Vector3Add(transform.transform.translation, Vector3RotateByAxisAngle(Vector3Scale(Vector3Normalize(Vector3Subtract(c1, c2)), 0.15f), Vector3{0,1,0}, static_cast<float>(GetRandomValue(0,30))));
					transform2.transform.translation = Vector3Add(transform2.transform.translation, Vector3RotateByAxisAngle(Vector3Scale(Vector3Normalize(Vector3Subtract(c2, c1)), 0.15f), Vector3{ 0,1,0 }, static_cast<float>(GetRandomValue(0, 30))));
				}

			}
		}
	}
}
