#pragma once

#include "Contract/entt_header_wrapper.h"

struct DamageRequest
{
	entt::entity target = entt::null;
	float damage = 0.f;
};