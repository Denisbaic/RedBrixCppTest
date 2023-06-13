#include "SpawnSystem.h"


#include "SpawnInfo.h"
#include "Implementation/TimerManager.h"
#include "Implementation/Factories/UnitFactory.h"

void SpawnSystem::execute(entt::registry & world)
{
	const auto view = world.view<SpawnInfo>();
	const auto current_time = TimerManager::instance().GetElapsedTime();
	
	for (auto& [entity,spawn_info] : view.each())
	{
		const auto need_to_spawn = current_time / spawn_info.spawn_rate;
		while(spawn_info.spawned <= spawn_info.units_to_spawn && spawn_info.spawned<need_to_spawn)
		{
			spawn_info.spawned++;

			UnitFactory::Create(world,spawn_info.pos, spawn_info.team, spawn_info.team_color);
		}
	}
}
