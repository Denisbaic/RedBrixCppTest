#pragma once
#include "raylib.h"
#include "Contract\EnttHeaderWeapper.h"


class RenderSystem
{
public:
	static void execute(entt::registry & world, const Camera& camera);
};