#pragma once
#include "raylib.h"
#include "Contract/entt_header_wrapper.h"


class RenderSystem
{
public:
	static void execute(entt::registry & world, const Camera& camera);
};