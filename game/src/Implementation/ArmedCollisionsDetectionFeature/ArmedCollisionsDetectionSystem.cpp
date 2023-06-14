#include "ArmedCollisionsDetectionSystem.h"

#include "ArmedMarker.h"
#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/CommonComponents/SphereInfo.h"
#include "Implementation/MoveFeature/TransformInfo.h"
#include "Implementation/SpawnFeature/UnitMarker.h"

#include "raymath.h"
#include "Implementation/DamageFeature/DamageRequest.h"
#include "Implementation/DamageFeature/HealthInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"

extern BoundingBox BoxComponentToBB(Vector3 pos, BoxInfo const& box_component);

void ArmedCollisionsDetectionSystem::execute(entt::registry& world)
{
	const auto units = world.view<TransformInfo, BoxInfo,TeamInfo, UnitMarker>();
	const auto armed = world.view<TransformInfo,SphereInfo, TeamInfo, ArmedMarker>();

	for (auto& [entity,transform_info,sphere_info,team_info]:armed.each())
	{
		for (auto& [unit, transform_info2, box_info, team2_info] : units.each())
		{
			if(team_info.team!= team2_info.team && CheckCollisionBoxSphere(BoxComponentToBB(transform_info2.transform.translation,box_info),
				Vector3Add(transform_info.transform.translation,sphere_info.pos),sphere_info.radius))
			{
				if(world.all_of<HealthInfo>(unit))
				{
					auto damage = world.get<HealthInfo>(unit).max_health / 5.f;

					auto damage_request = world.create();
					world.emplace<DamageRequest>(damage_request, unit,damage);
				}
				world.destroy(entity);
			}
		}
	}
}