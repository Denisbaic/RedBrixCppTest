#pragma once
#include "Contract\EnttHeaderWeapper.h"

struct WeaponInfo
{
    float attack_range = 1.f;
    float attack_delay = 1.f;
	entt::entity projectile = entt::null;
};