#include "ArrowFactory.h"

#include "Implementation/MoveFeature/TransformInfo.h"

#include "raymath.h"
#include "Implementation/ArmedCollisionsDetectionFeature/ArmedMarker.h"
#include "Implementation/CommonComponents/CapsuleInfo.h"
#include "Implementation/CommonComponents/SphereInfo.h"
#include "Implementation/CommonComponents/TimerInfo.h"
#include "Implementation/FlightFeature/FlightInfo.h"
#include "Implementation/RenderFeature/RenderableMarker.h"
#include "Implementation/TeamFeature/TeamInfo.h"


entt::entity ArrowFactory::Create(entt::registry& world, Vector3 P0, Vector3 P1, Vector3 P2,float flight_time, Team team)
{
	const auto new_entity = world.create();

	Assign(world, new_entity, P0, P1, P2, flight_time, team);

	return new_entity;
}

entt::entity ArrowFactory::Create(entt::registry& world, Vector3 begin, Vector3 end, float flight_height, float flight_time,
	Team team)
{
	Vector3 P1 = Vector3SubtractValue(Vector3Add(begin, end), 2.f);
	P1.y = begin.y + flight_height;

	return Create(world, begin, P1, end, flight_time, team);
}

void ArrowFactory::Assign(entt::registry& world, entt::entity entity_id, Vector3 P0, Vector3 P1, Vector3 P2,
	float flight_time, Team team)
{
	std::ignore = world.get_or_emplace<CapsuleInfo>(entity_id, Vector3{ 0,0.5,0 }, Vector3{ 0,-0.5,0 }, 0.5f, 8, 8, BROWN);
	std::ignore = world.get_or_emplace<SphereInfo>(entity_id, Vector3{ 0,0.5,0 }, 0.6f, GRAY);

	world.emplace_or_replace<TransformInfo>(entity_id, entt::null, Transform{ P0,QuaternionFromEuler(0,0,0),{1,1,1} });
	world.emplace_or_replace<FlightInfo>(entity_id, P0, P1, P2, flight_time);
	world.emplace_or_replace<TeamInfo>(entity_id, team);
	world.emplace_or_replace<TimerInfo>(entity_id, 0.f);
	world.emplace_or_replace<ArmedMarker>(entity_id);
	world.emplace_or_replace<RenderableMarker>(entity_id);
}

void ArrowFactory::Assign(entt::registry& world, entt::entity entity_id, Vector3 begin, Vector3 end,
                          float flight_height, float flight_time, Team team)
{
	Vector3 P1 = Vector3SubtractValue(Vector3Add(begin, end), 2.f);
	P1.y = begin.y + flight_height;

	Assign(world, entity_id, begin, P1, end, flight_time, team);
}
