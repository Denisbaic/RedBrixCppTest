#pragma once

#include "raylib.h"
#include "Contract/entt_header_wrapper.h"
#include "Implementation/TeamFeature/TeamEnum.h"

class ArrowFactory
{
public:

	static entt::entity Create(entt::registry& world, Vector3 P0, Vector3 P1, Vector3 P2, float flight_time, Team team);
	static entt::entity Create(entt::registry& world, Vector3 begin, Vector3 end,float flight_height, float flight_time, Team team);

	static void Assign(entt::registry& world, entt::entity entity_id, Vector3 P0, Vector3 P1, Vector3 P2, float flight_time, Team team);
	static void Assign(entt::registry& world, entt::entity entity_id, Vector3 begin, Vector3 end, float flight_height, float flight_time, Team team);
};