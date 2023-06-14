#pragma once
#include "raylib.h"
#include "Contract/EnttHeaderWeapper.h"

class RenderSystem
{
public:
	static void Execute(entt::registry & world, const Camera& camera);
};