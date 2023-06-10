#pragma once
#include "Contract/IGame.h"

#include "Contract/entt_header_wrapper.h"

#include "raylib.h"
#include "raymath.h"

struct TransformComponent
{
	Vector3 position;
};

struct BoxComponent
{
	Vector3 local_offset;
	Vector3 size;
	Color color;
};

enum class Team
{
	Blue,
	Red
};

struct ArcherComponent
{
	Team team;
};

struct CapsuleComponent
{
	Vector3 begin;
	Vector3 end;
	float radius;
	int slices;
	int rings;
	Color color;
};

class ArcherGame : public IGame
{
public:
	void PreInit(std::any const& config) override;
	void BeginPlay() override;
	void Tick(double DeltaSeconds) override;
	void Render() override;

protected:
	Camera camera_ = { { 0.0f, 80.0f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

	entt::registry world_;

	void EndPlay() override;

public:
	~ArcherGame() override = default;
};

