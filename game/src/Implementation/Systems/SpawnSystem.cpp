#include "SpawnSystem.h"

#include <iostream>

#include "Implementation/ArcherGame.h"
#include "Implementation/Components/SpawnInfoComponent.h"
#include "Implementation/TimerManager.h"

void SpawnSystem::execute(entt::registry & world)
{
	const auto view = world.view<SpawnInfoComponent>();
	const auto current_time = TimerManager::instance().GetElapsedTime();
	auto t = view.size();
	for (auto& [entity,spawn_info] : view.each())
	{
		const auto need_to_spawn = current_time / spawn_info.spawn_rate;;
		while(spawn_info.spawned <= spawn_info.units_to_spawn && spawn_info.spawned<need_to_spawn)
		{
			spawn_info.spawned++;
			
			const auto new_entity = world.create();
			world.emplace<TransformComponent>(new_entity, spawn_info.pos);
			world.emplace<BoxComponent>(new_entity, Vector3{ 0,0,0 }, Vector3{ 1,1,1 }, spawn_info.team_color);
			world.emplace<ArcherComponent>(new_entity, spawn_info.team);
		}
	}
}
