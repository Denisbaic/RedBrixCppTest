#include "AvoidCollisionsSystem.h"

#include "TransformInfo.h"
#include "Implementation/SpawnFeature/UnitMarker.h"
#include "Implementation/ArcherGame.h"
#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/Utils/MathUtils.h"

#include "raymath.h"

void AvoidCollisionsSystem::Execute(entt::registry& world)
{
	const auto units = world.view<TransformInfo, BoxInfo, UnitMarker>();

	for (auto& [entity, transform, box] : units.each())
	{
		for (auto& [entity2, transform2, box2] : units.each())
		{
			if(entity != entity2 && CheckCollisionBoxes(MathUtils::BoxComponentToBB(transform.transform.translation,box), MathUtils::BoxComponentToBB(transform2.transform.translation, box2)))
			{
				auto c1 = Vector3Add(MathUtils::BoxComponentToBB(transform.transform.translation, box).min, MathUtils::BoxComponentToBB(transform.transform.translation, box).max);
				c1 = { c1.x / 2.f,c1.y / 2.f, c1.z / 2.f };
				auto c2 = Vector3Add(MathUtils::BoxComponentToBB(transform2.transform.translation, box2).min, MathUtils::BoxComponentToBB(transform2.transform.translation, box2).max);
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
