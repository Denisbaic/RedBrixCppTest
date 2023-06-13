#pragma once
#include "Contract/entt_header_wrapper.h"



struct WeaponInfo
{
    float attack_range = 1.f;
    float attack_delay = 1.f;
	entt::entity projectile = entt::null;
};