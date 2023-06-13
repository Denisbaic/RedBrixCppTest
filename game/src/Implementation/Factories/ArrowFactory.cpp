#include "ArrowFactory.h"

#include "Implementation/MoveFeature/TransformInfo.h"

#include "raymath.h"
#include "Implementation/CommonComponents/CapsuleInfo.h"
#include "Implementation/CommonComponents/SphereInfo.h"
#include "Implementation/CommonComponents/TimerInfo.h"
#include "Implementation/FlightFeature/FlightInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"


entt::entity ArrowFactory::Create(entt::registry& world, Vector3 P0, Vector3 P1, Vector3 P2,float flight_time, Team team)
{
	const auto new_entity = world.create();
	
	world.emplace<TransformInfo>(new_entity, entt::null, Transform{ P0,QuaternionFromEuler(0,0,0),{1,1,1} });
	world.emplace<FlightInfo>(new_entity, P0, P1, P2, flight_time);
	world.emplace<CapsuleInfo>(new_entity, Vector3{ 0,0.5,0 }, Vector3{ 0,-0.5,0 }, 0.5f, 8, 8, BROWN);
	world.emplace<SphereInfo>(new_entity, Vector3{ 0,0.5,0 },0.6f, GRAY);
	world.emplace<TeamInfo>(new_entity, team);
	world.emplace<TimerInfo>(new_entity, 0.f);

	return new_entity;
}

entt::entity ArrowFactory::Create(entt::registry& world, Vector3 begin, Vector3 end, float flight_height, float flight_time,
	Team team)
{
	Vector3 P1 = Vector3SubtractValue(Vector3Add(begin, end), 2.f);
	P1.y = begin.y + flight_height;

	return Create(world, begin, P1, end, flight_time, team);
}
