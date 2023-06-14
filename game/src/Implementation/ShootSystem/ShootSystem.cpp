#include "ShootSystem.h"

#include "ShootRequest.h"
#include "Implementation/MoveFeature/TransformInfo.h"
#include "Implementation/Utils/EnttUtils.h"
#include "Implementation/WeaponFeature/WeaponInfo.h"
#include "Implementation/FlightFeature/FlightInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"
#include "Implementation/Factories/ArrowFactory.h"
#include "Implementation/ReloadingFeature/ReloadingMarker.h"


void ShootSystem::execute(entt::registry& world)
{
	const auto shoot_requests = world.view<ShootRequest>();

	for (auto [entity,shoot_request] : shoot_requests.each())
	{
		if (shoot_request.weapon != entt::null && shoot_request.target != entt::null)
		{
			auto&& [owner_team,pos_info] = world.get<TeamInfo,TransformInfo>(shoot_request.owner);
			auto& target_pos_info = world.get<TransformInfo>(shoot_request.target);
			auto& weapon_info = world.get<WeaponInfo>(shoot_request.weapon);
			auto projectile_instance = EnttUtils::CreateCopy(world, weapon_info.projectile);

			ArrowFactory::Assign(world, projectile_instance, pos_info.transform.translation, target_pos_info.transform.translation, 5.f, 2.f,owner_team.team);

			//TODO add request
			world.emplace_or_replace<ReloadingMarker>(shoot_request.weapon);
		}
		world.destroy(entity);
	}
}
