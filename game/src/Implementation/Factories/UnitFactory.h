#pragma once
#include "raylib.h"
#include "Contract/EnttHeaderWeapper.h"

#include "Implementation/TeamFeature/ETeam.h"

class UnitFactory
{
public:
	static entt::entity Create(entt::registry& world, Vector3 pos, ETeam team, Color team_color);

	static void AssignWeapon(entt::registry& world, entt::entity id, entt::entity weapon);
};