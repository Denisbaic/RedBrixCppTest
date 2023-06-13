#include "ArcherGame.h"

#include <chrono>

#include "TimerManager.h"
#include "CommonComponents/BoxInfo.h"
#include "DamageFeature/DamageSystem.h"
#include "MoveFeature/AvoidCollisionsSystem.h"
#include "MoveFeature/MoveSystem.h"
#include "RenderFeature/RenderSystem.h"
#include "SpawnFeature/SpawnInfo.h"
#include "SpawnFeature/SpawnSystem.h"
#include "TeamFeature/TeamEnum.h"
#include "WeaponFeature/WeaponSystem.h"

entt::entity create_copy(entt::registry& world, entt::entity id)
{
	auto new_entity = world.create(id);

	// create a copy of an entity component by component
	for (auto&& curr : world.storage()) {
		if (auto& storage = curr.second; storage.contains(id)) {
			storage.emplace(new_entity, storage.get(id));

		}
	}

	return new_entity;
}


void ArcherGame::PreInit(std::any const& config)
{
	auto RedSpawner = world_.create();
	world_.emplace<SpawnInfo>(RedSpawner, std::chrono::milliseconds{100}, 20,0, Vector3{ 10.f,0.f,10.f },RED,Team::Red);
	
	auto BlueSpawner = world_.create();
	world_.emplace<SpawnInfo>(BlueSpawner, std::chrono::milliseconds{100}, 20,0, Vector3{ 40.f,0.f,40.f },BLUE, Team::Blue);

}

void ArcherGame::BeginPlay()
{
	TimerManager::instance().Restart();
}

void ArcherGame::Tick(double DeltaSeconds)
{
	SpawnSystem::execute(world_);

	MoveSystem::execute(world_);
	AvoidCollisionsSystem::execute(world_);
	WeaponSystem::execute(world_);
	DamageSystem::execute(world_);
}

void ArcherGame::Render()
{
	RenderSystem::execute(world_, camera_);
}

void ArcherGame::EndPlay()
{
	world_.clear<>();
}
