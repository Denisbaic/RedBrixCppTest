#pragma once
#include "raylib.h"
#include "Contract/IGame.h"

#include "Contract/entt_header_wrapper.h"


class ArcherGame final: public IGame
{
public:
	void PreInit(std::any const& config) override;
	void BeginPlay() override;
	void Tick(double DeltaSeconds) override;
	void Render() override;

protected:
	Camera camera_ = { { -40.0f, 40, 80 }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_ORTHOGRAPHIC };

	entt::registry world_;

	void EndPlay() override;

public:
	~ArcherGame() override = default;
};

