#pragma once
#include <chrono>

#include "raylib.h"
#include "Implementation/TeamFeature/ETeam.h"

struct SpawnInfo
{	
	std::chrono::milliseconds spawn_rate= std::chrono::milliseconds{ 100 };
	int units_to_spawn = 0;
	int spawned = 0;
	Vector3 pos{};
	Color team_color{};
	ETeam team = ETeam::Neutral;
};

