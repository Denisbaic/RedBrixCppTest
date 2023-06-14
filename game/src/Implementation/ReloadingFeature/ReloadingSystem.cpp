#include "ReloadingSystem.h"

#include "ReloadingMarker.h"
#include "ReloadingRequest.h"
#include "Implementation/CommonComponents/TimerInfo.h"
#include "Implementation/WeaponFeature/WeaponInfo.h"

void ReloadingSystem::Execute(entt::registry & world,float dt)
{
	const auto weapons_on_reloading = world.view<WeaponInfo,TimerInfo, ReloadingMarker>();

	for (auto& [entity,weapon_info,timer_info] : weapons_on_reloading.each())
	{
		timer_info.t += dt;
		if (weapon_info.attack_delay<= timer_info.t)
		{
			world.erase<ReloadingMarker>(entity);
			timer_info.t = 0.f;
		}
	}

	const auto reloading_requests = world.view<ReloadingRequest>();
    for (auto& [entity,reloading_request]: reloading_requests.each())
    {
	    if (world.valid(reloading_request.weapon))
	    {
			world.emplace_or_replace<ReloadingMarker>(reloading_request.weapon);
	    }
		world.destroy(entity);
    }
}
