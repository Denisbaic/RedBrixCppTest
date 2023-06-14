#include "ArcherGame.h"

#include <chrono>

#include "ArmedCollisionsDetectionFeature/ArmedCollisionsDetectionSystem.h"
#include "CommonComponents/BoxInfo.h"
#include "CommonComponents/CapsuleInfo.h"
#include "CommonComponents/SphereInfo.h"
#include "DamageFeature/DamageSystem.h"
#include "DeathFeature/DeathSystem.h"
#include "FlightFeature/FlightSystem.h"
#include "MoveFeature/AvoidCollisionsSystem.h"
#include "MoveFeature/MoveSystem.h"
#include "ReloadingFeature/ReloadingSystem.h"
#include "RenderFeature/RenderSystem.h"
#include "ShootSystem/ShootSystem.h"
#include "SpawnFeature/SpawnInfo.h"
#include "SpawnFeature/SpawnSystem.h"
#include "TeamFeature/ETeam.h"
#include "Utils/TimerManager.h"
#include "WeaponFeature/WeaponSystem.h"

entt::entity arrow_prototype = entt::null;

void ArcherGame::PreInit(std::any const& config)
{
	arrow_prototype = world_.create();
	world_.emplace<CapsuleInfo>(arrow_prototype, Vector3{ 0,0.f,0 }, Vector3{ 0.5f,0,0 }, 0.1f, 8, 8, BROWN);
	world_.emplace<SphereInfo>(arrow_prototype, Vector3{ 0,0.f,0 }, 0.2f, GRAY);

	auto RedSpawner = world_.create();
	world_.emplace<SpawnInfo>(RedSpawner, std::chrono::milliseconds{100}, 20,0, Vector3{ -20.f,0.f,-20.f },RED,ETeam::Red);
	
	auto BlueSpawner = world_.create();
	world_.emplace<SpawnInfo>(BlueSpawner, std::chrono::milliseconds{100}, 20,0, Vector3{ 20.f,0.f,20.f },BLUE, ETeam::Blue);
}

void ArcherGame::BeginPlay()
{
	TimerManager::instance().Restart();
}

void ArcherGame::Tick(double dt)
{
	SpawnSystem::Execute(world_);
	MoveSystem::Execute(world_);
	AvoidCollisionsSystem::Execute(world_);
	WeaponSystem::Execute(world_);
	ShootSystem::Execute(world_);
	ReloadingSystem::Execute(world_,static_cast<float>(dt));
	ArmedCollisionsDetectionSystem::Execute(world_);
	DamageSystem::Execute(world_);
	FlightSystem::execute(world_);
	DeathSystem::Execute(world_);
}

void ArcherGame::Render()
{
	RenderSystem::Execute(world_, camera_);
}

void ArcherGame::EndPlay()
{
	world_.clear();
}
