#pragma once

#include "Contract\EnttHeaderWeapper.h"

struct ShootRequest
{
	entt::entity owner = entt::null;

	entt::entity target = entt::null;
	entt::entity weapon = entt::null;
};