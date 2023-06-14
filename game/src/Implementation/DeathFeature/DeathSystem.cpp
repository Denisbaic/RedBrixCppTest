#include "DeathSystem.h"

#include "Implementation/DamageFeature/HealthInfo.h"
#include "Implementation/WeaponFeature/HasWeaponInfo.h"

#include "raymath.h"

void DeathSystem::Execute(entt::registry& world)
{
	const auto view = world.view<HealthInfo>();

	for (auto& [entity,health] : view.each())
	{
		if(FloatEquals(health.current_health,0.f))
		{
			if(world.all_of<HasWeaponInfo>(entity))
			{
				world.destroy(world.get<HasWeaponInfo>(entity).weapon);
			}
			world.destroy(entity);
		}
	}
}
