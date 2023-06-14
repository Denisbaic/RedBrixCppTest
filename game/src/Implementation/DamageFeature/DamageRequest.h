#pragma once

#include "Contract\EnttHeaderWeapper.h"

struct DamageRequest
{
	entt::entity target = entt::null;
	float damage = 0.f;
};