#pragma once
#include "raylib.h"
#include "Implementation/CommonComponents/BoxInfo.h"

class MathUtils
{
public:
    static Vector3 InterpConstantTo(Vector3 const& Current, Vector3 const& Target, float DeltaTime, float InterpSpeed);

    static BoundingBox BoxComponentToBB(Vector3 pos, BoxInfo const& box_component);
};
