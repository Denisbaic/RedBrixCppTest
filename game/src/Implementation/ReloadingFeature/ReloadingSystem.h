#pragma once

#include "Contract/entt_header_wrapper.h"

class ReloadingSystem
{
public:
	static void execute(entt::registry& world, float DeltaSeconds);
};
