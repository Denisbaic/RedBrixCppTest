#pragma once
#include "raylib.h"

struct FlightInfo
{
	Vector3 P0;
	Vector3 P1;
	Vector3 P2;

    /*[0..1]*/
	float t;
};
