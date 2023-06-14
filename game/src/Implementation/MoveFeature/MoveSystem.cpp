#include "MoveSystem.h"

#include <chrono>

#include "MoveableMarker.h"
#include "Implementation/ArcherGame.h"
#include "TransformInfo.h"
#include "Implementation/SpawnFeature/UnitMarker.h"
#include "Implementation/Utils/TimerManager.h"
#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"
#include "Implementation/Utils/MathUtils.h"

#include "raymath.h"
#include "Implementation/WeaponFeature/HasWeaponInfo.h"
#include "Implementation/WeaponFeature/WeaponInfo.h"

void MoveSystem::Execute(entt::registry& world)
{
	const auto units = world.view<TransformInfo, BoxInfo, TeamInfo,HasWeaponInfo, UnitMarker,MoveableMarker>();

	for (auto& [entity,transform_info,box_info,team_info,has_weapon_info] : units.each())
	{
		const auto current_team = team_info.team;

		float min_dist = std::numeric_limits<float>::max();
		auto min_entity = entity;
		for (auto& [entity2, transform_info2, box_info2, team_info2, has_weapon_info2] : units.each())
		{
			const float current_dist = Vector3Distance(transform_info.transform.translation, transform_info2.transform.translation);
			if(min_dist>current_dist && team_info2.team!=current_team)
			{
				min_dist = current_dist;
				min_entity = entity2;
			}
		}

		if(min_dist>  ((world.valid(has_weapon_info.weapon)&&world.all_of<WeaponInfo>(has_weapon_info.weapon)) ? world.get<WeaponInfo>(has_weapon_info.weapon).attack_range : 20.f))
		{
			auto& t2 = units.get<TransformInfo>(min_entity).transform.translation;
			transform_info.transform.translation = MathUtils::InterpConstantTo(transform_info.transform.translation, t2, std::chrono::duration<float>(TimerManager::instance().MS_PER_UPDATE).count(), 3.f);
		}
	}
}
