#pragma once
#include <chrono>

#include "raylib.h"

struct SpawnInfoComponent
{	
	std::chrono::milliseconds spawn_rate= std::chrono::milliseconds{ 100 };
	int units_to_spawn = 0;
	int spawned = 0;
	Vector3 pos;
	Color team_color;
	Team team;
};

