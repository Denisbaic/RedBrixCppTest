#include "MoveSystem.h"

#include <chrono>

#include "MoveableMarker.h"
#include "Implementation/ArcherGame.h"
#include "TransformInfo.h"
#include "Implementation/SpawnFeature/UnitMarker.h"
#include "Implementation/Utils/TimerManager.h"
#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"

#include "raymath.h"



extern Vector3 InterpConstantTo(Vector3 const& Current, Vector3 const& Target, float DeltaTime, float InterpSpeed);

void MoveSystem::execute(entt::registry& world)
{
	const auto view = world.view<TransformInfo, BoxInfo, TeamInfo,UnitMarker,MoveableMarker>();

	for (auto& [entity,transform,box,t] : view.each())
	{
		const auto current_team = t.team;

		float min_dist = std::numeric_limits<float>::max();
		auto min_entity = entity;
		for (auto& [entity2, transform2, box2, t2] : view.each())
		{
			const float current_dist = Vector3Distance(transform.transform.translation, transform2.transform.translation);
			if(min_dist>current_dist && t2.team!=current_team)
			{
				min_dist = current_dist;
				min_entity = entity2;
			}
		}

		if(min_dist>20.f)
		{
			auto& t2 = view.get<TransformInfo>(min_entity).transform.translation;
			transform.transform.translation = InterpConstantTo(transform.transform.translation, t2, std::chrono::duration<float>(TimerManager::instance().MS_PER_UPDATE).count(), 3.f);
		}
	}
}
