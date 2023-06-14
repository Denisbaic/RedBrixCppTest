#pragma once

#include "Contract\EnttHeaderWeapper.h"

class ReloadingSystem
{
public:
	static void execute(entt::registry& world, float DeltaSeconds);
};
