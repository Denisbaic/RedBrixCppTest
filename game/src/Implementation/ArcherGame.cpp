#include "ArcherGame.h"

#include "ImageManager.h"

#include <iostream>

#include "TimerManager.h"
#include "Implementation/Components/TimeComponent.h"
#include "Implementation/Components/SpawnInfoComponent.h"
#include "Systems/AvoidCollisions.h"
#include "Systems/MoveSystem.h"
#include "Systems/SpawnSystem.h"

void ArcherGame::PreInit(std::any const& config)
{
	auto RedSpawner = world_.create();
	//world_.emplace<TimeComponent>(RedSpawner, std::chrono::milliseconds{0});
	world_.emplace<SpawnInfoComponent>(RedSpawner, std::chrono::milliseconds{100}, 20,0, Vector3{ 10.f,0.f,10.f },RED,Team::Red);

	auto BlueSpawner = world_.create();
	//world_.emplace<TimeComponent>(BlueSpawner, std::chrono::milliseconds{0});
	world_.emplace<SpawnInfoComponent>(BlueSpawner, std::chrono::milliseconds{100}, 20,0, Vector3{ 40.f,0.f,40.f },BLUE, Team::Blue);
	/*
	for (int i = 0; i < 5; ++i)
	{
		auto entity = world_.create();
		world_.emplace<TransformComponent>(entity, 10.f, 0.0f, 10.f);
		world_.emplace<BoxComponent>(entity, Vector3{ 0,0,0 }, Vector3{ 1,1,1 }, RED);
	}

	for (int i = 0; i < 5; ++i)
	{
		auto entity = world_.create();
		world_.emplace<TransformComponent>(entity,40.f, 0.f, 40.f);
		world_.emplace<BoxComponent>(entity, Vector3{ 0,0,0 }, Vector3{ 1,1,1 }, BLUE);
	}
	*/
}

void ArcherGame::BeginPlay()
{
	TimerManager::instance().Restart();
}

void ArcherGame::Tick(double DeltaSeconds)
{
	SpawnSystem::execute(world_);

	MoveSystem::execute(world_);
	AvoidCollisions::execute(world_);
	/*
	auto view = world_.view<TransformComponent>();

	for (auto [entity, pos] : view.each()) {
		pos.position.z += 1.f* DeltaSeconds;
	}
	*/
}

void ArcherGame::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);
	BeginMode3D(camera_);

	DrawGrid(100, 1.0f);

	auto view = world_.view<TransformComponent, BoxComponent>();
	for (auto [entity, pos, box] : view.each()) {
		DrawCubeV(Vector3Add(pos.position, box.local_offset), box.size, box.color);
	}

	EndMode3D();
	EndDrawing();
}

void ArcherGame::EndPlay()
{
	world_.clear<>();
}
