#pragma once
#include "raylib.h"
#include "Contract/entt_header_wrapper.h"

struct TransformInfo
{
	entt::entity owner;
	Transform transform;
};