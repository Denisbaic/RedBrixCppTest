#include "SpawnSystem.h"


#include "SpawnInfo.h"
#include "Implementation/Factories/BowFactory.h"
#include "Implementation/Factories/UnitFactory.h"
#include "Implementation/Utils/TimerManager.h"

extern entt::entity arrow_prototype;

void SpawnSystem::execute(entt::registry & world)
{
	const auto view = world.view<SpawnInfo>();
	const auto current_time = TimerManager::instance().GetElapsedTime();
	
	for (auto& [entity,spawn_info] : view.each())
	{
		const auto need_to_spawn = current_time / spawn_info.spawn_rate;
		while(spawn_info.spawned < spawn_info.units_to_spawn && spawn_info.spawned<need_to_spawn)
		{
			spawn_info.spawned++;

			auto bow = BowFactory::Create(world, 20.f, 1.f, arrow_prototype);
			auto unit = UnitFactory::Create(world,spawn_info.pos, spawn_info.team, spawn_info.team_color);
			UnitFactory::AssignWeapon(world, unit, bow);
		}
	}
}
