#pragma once
#include "raylib.h"
#include "Contract/entt_header_wrapper.h"

#include "Implementation/TeamFeature/TeamEnum.h"

class UnitFactory
{
public:
	static entt::entity Create(entt::registry& world, Vector3 pos, Team team, Color team_color);

	static void AssignWeapon(entt::registry& world, entt::entity id, entt::entity weapon);
};