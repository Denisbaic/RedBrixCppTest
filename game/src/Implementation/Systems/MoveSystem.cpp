#include "MoveSystem.h"

#include <iostream>

#include "Implementation/ArcherGame.h"
#include "raymath.h"
#include "Implementation/TimerManager.h"

extern Vector3 InterpConstantTo(Vector3 const& Current, Vector3 const& Target, float DeltaTime, float InterpSpeed);


void MoveSystem::execute(entt::registry& world)
{
	const auto view = world.view<TransformComponent, BoxComponent,ArcherComponent>();

	for (auto& [entity,transform,box,t] : view.each())
	{
		const auto current_team = t.team;

		float min_dist = std::numeric_limits<float>::max();
		auto min_entity = entity;
		for (auto& [entity2, transform2, box2, t2] : view.each())
		{
			float current_dist = Vector3Distance(transform.position, transform2.position);
			if(min_dist>current_dist && t2.team!=current_team)
			{
				min_dist = current_dist;
				min_entity = entity2;
			}
		}

		if(min_dist>20.f)
		{
			std::cout << min_dist << std::endl;
			auto& t2 = view.get<TransformComponent>(min_entity).position;
			transform.position = InterpConstantTo(transform.position, t2, std::chrono::duration<float>(TimerManager::instance().MS_PER_UPDATE).count(), 3.f);
		}
	}
}
