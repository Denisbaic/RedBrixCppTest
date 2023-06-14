#include "WeaponSystem.h"

#include "HasWeaponInfo.h"
#include "WeaponInfo.h"
#include "Implementation/CommonComponents/TimerInfo.h"
#include "Implementation/ReloadingFeature/ReloadingMarker.h"
#include "Implementation/SpawnFeature/UnitMarker.h"
#include "Implementation/TeamFeature/TeamInfo.h"
#include "Implementation/MoveFeature/TransformInfo.h"
#include "Implementation/ShootSystem/ShootRequest.h"

#include "raymath.h"

void WeaponSystem::Execute(entt::registry & world)
{
	const auto weapons_ready_to_shoot = world.view<WeaponInfo, TimerInfo>(entt::exclude<ReloadingMarker>);
	const auto units = world.view<TransformInfo,HasWeaponInfo, TeamInfo,UnitMarker>();

	for (auto [entity,transform_info, has_weapon_info,team_info] : units.each())
	{
		if(weapons_ready_to_shoot.contains(has_weapon_info.weapon))
		{
			entt::entity closest = entt::null;
			float min_dist = std::numeric_limits<float>::max();

			for (auto [entity2, transform_info2, has_weapon_info2, team_info2] : units.each())
			{
				const float current_distance = Vector3Distance(transform_info.transform.translation, transform_info2.transform.translation);
				if(team_info.team!=team_info2.team && current_distance <min_dist)
				{
					closest = entity2;
					min_dist = current_distance;
				}
			}

			if(min_dist <= weapons_ready_to_shoot.get<WeaponInfo>(has_weapon_info.weapon).attack_range)
			{
				const auto shoot_request = world.create();
				world.emplace<ShootRequest>(shoot_request, entity, closest, has_weapon_info.weapon);
			}
		}
	}
}
