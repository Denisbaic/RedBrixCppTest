#pragma once
#include "raylib.h"

struct CapsuleInfo
{
	Vector3 begin;
	Vector3 end;
	float radius;
	int slices;
	int rings;
	Color color;
};