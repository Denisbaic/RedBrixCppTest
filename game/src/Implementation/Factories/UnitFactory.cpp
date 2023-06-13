#include "UnitFactory.h"

#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/MoveFeature/TransformInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"
#include "Implementation/MoveFeature/MoveableMarker.h"
#include "Implementation/RenderFeature/RenderableMarker.h"
#include "Implementation/SpawnFeature/UnitMarker.h"

#include "raymath.h"

entt::entity UnitFactory::Create(entt::registry& world, Vector3 pos, Team team, Color team_color)
{
	const auto new_entity = world.create();

	world.emplace<TransformInfo>(new_entity, entt::null, Transform{ pos,QuaternionFromEuler(0,0,0),{1,1,1} });
	world.emplace<BoxInfo>(new_entity, Vector3{ 0,0,0 }, Vector3{ 1,1,1 }, team_color);
	world.emplace<TeamInfo>(new_entity, team);

	world.emplace<UnitMarker>(new_entity);
	world.emplace<RenderableMarker>(new_entity);
	world.emplace<MoveableMarker>(new_entity);

	return new_entity;
}
