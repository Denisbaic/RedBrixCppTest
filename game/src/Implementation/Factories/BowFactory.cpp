#include "BowFactory.h"

#include "Implementation/CommonComponents/TimerInfo.h"
#include "Implementation/WeaponFeature/WeaponInfo.h"

entt::entity BowFactory::Create(entt::registry& world, float attack_range, float attack_cooldown,
                                entt::entity projectile_prototype)
{
	const auto new_entity = world.create();

	world.emplace<WeaponInfo>(new_entity, attack_range, attack_cooldown, projectile_prototype);
	world.emplace<TimerInfo>(new_entity, 0.f);
	
	return new_entity;
}
