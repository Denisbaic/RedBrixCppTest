#pragma once
#include "raylib.h"

struct FlightInfo
{
	Vector3 P0{};
	Vector3 P1{};
	Vector3 P2{};

	float total_time = 0.f;
    /*[0..1]*/
	float t = 0.f;
};
