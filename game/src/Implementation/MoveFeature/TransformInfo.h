#pragma once
#include "raylib.h"
#include "Contract/EnttHeaderWeapper.h"

struct TransformInfo
{
	entt::entity owner;
	Transform transform;
};