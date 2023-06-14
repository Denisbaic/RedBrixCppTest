#include "UnitFactory.h"

#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/MoveFeature/TransformInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"
#include "Implementation/MoveFeature/MoveableMarker.h"
#include "Implementation/RenderFeature/RenderableMarker.h"
#include "Implementation/SpawnFeature/UnitMarker.h"

#include "raymath.h"
#include "Implementation/DamageFeature/HealthInfo.h"
#include "Implementation/WeaponFeature/HasWeaponInfo.h"

entt::entity UnitFactory::Create(entt::registry& world, Vector3 pos, Team team, Color team_color)
{
	const auto new_entity = world.create();

	world.emplace<TransformInfo>(new_entity, entt::null, Transform{ pos,QuaternionFromEuler(0,0,0),{1,1,1} });
	world.emplace<BoxInfo>(new_entity, Vector3{ 0,0,0 }, Vector3{ 0.25f,1.7f,0.25f }, team_color);
	world.emplace<TeamInfo>(new_entity, team);
	world.emplace<HealthInfo>(new_entity, 10.f, 10.f);

	world.emplace<UnitMarker>(new_entity);
	world.emplace<RenderableMarker>(new_entity);
	world.emplace<MoveableMarker>(new_entity);

	return new_entity;
}

void UnitFactory::AssignWeapon(entt::registry& world, entt::entity id,entt::entity weapon)
{
	world.emplace_or_replace<HasWeaponInfo>(id, weapon);
}
