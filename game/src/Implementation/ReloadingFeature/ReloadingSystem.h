#pragma once

#include "Contract/EnttHeaderWeapper.h"

class ReloadingSystem
{
public:
	static void Execute(entt::registry& world, float dt);
};
