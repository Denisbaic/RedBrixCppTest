#pragma once

#include "Contract/entt_header_wrapper.h"

struct ShootRequest
{
	entt::entity owner = entt::null;

	entt::entity target = entt::null;
	entt::entity weapon = entt::null;
};