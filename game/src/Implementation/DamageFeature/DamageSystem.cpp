#include "DamageSystem.h"

#include "DamageRequest.h"
#include "HealthInfo.h"

#include "raymath.h"

void DamageSystem::Execute(entt::registry& world)
{
	const auto damage_requests = world.view<DamageRequest>();
	for (auto& [entity, damage_request] : damage_requests.each())
	{
		if (world.valid(damage_request.target) && world.all_of<HealthInfo>(damage_request.target))
		{
			auto& health = world.get<HealthInfo>(damage_request.target);
			health.current_health = Clamp(health.current_health - damage_request.damage, 0.f, health.max_health);
		}
		
		world.destroy(entity);
	}
}
