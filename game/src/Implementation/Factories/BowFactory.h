#pragma once
#include "Contract/entt_header_wrapper.h"

class BowFactory
{
public:
	static entt::entity Create(entt::registry& world, float attack_range, float attack_cooldown ,entt::entity projectile_prototype);
};

