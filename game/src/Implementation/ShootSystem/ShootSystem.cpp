#include "ShootSystem.h"

#include "ShootRequest.h"
#include "Implementation/MoveFeature/TransformInfo.h"
#include "Implementation/Utils/EnttUtils.h"
#include "Implementation/WeaponFeature/WeaponInfo.h"
#include "Implementation/FlightFeature/FlightInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"
#include "Implementation/Factories/ArrowFactory.h"
#include "Implementation/ReloadingFeature/ReloadingMarker.h"
#include "Implementation/ReloadingFeature/ReloadingRequest.h"

void ShootSystem::Execute(entt::registry& world)
{
	const auto shoot_requests = world.view<ShootRequest>();

	for (auto [entity,shoot_request] : shoot_requests.each())
	{
		if (shoot_request.weapon != entt::null && shoot_request.target != entt::null && 
			!world.all_of<ReloadingMarker>(shoot_request.weapon))
		{
			auto&& [owner_team,pos_info] = world.get<TeamInfo,TransformInfo>(shoot_request.owner);
			const auto& target_pos_info = world.get<TransformInfo>(shoot_request.target);
			const auto& weapon_info = world.get<WeaponInfo>(shoot_request.weapon);
			const auto projectile_instance = EnttUtils::CreateCopy(world, weapon_info.projectile);

			ArrowFactory::Assign(world, projectile_instance, pos_info.transform.translation, target_pos_info.transform.translation, 5.f, 2.f,owner_team.team);

			const auto reloading_request = world.create();
			world.emplace_or_replace<ReloadingRequest>(reloading_request, shoot_request.weapon);
		}
		world.destroy(entity);
	}
}
