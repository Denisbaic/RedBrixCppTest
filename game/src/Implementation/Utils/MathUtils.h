#pragma once
#include "raylib.h"
#include "Implementation/CommonComponents/BoxInfo.h"

class MathUtils
{
public:
    static Vector3 InterpConstantTo(Vector3 const& current, Vector3 const& target, float dt, float interp_speed);

    static BoundingBox BoxComponentToBB(Vector3 pos, BoxInfo const& box_component);
};
